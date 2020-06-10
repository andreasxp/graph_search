#pragma once
#include <stdexcept>
#include <future>
#include <iostream>

#include "puff.hpp"
#include "level_builder/level_builder.hpp"
#include "zh/util/assert.hpp"

namespace zh {

namespace {
	template <class T, class U>
	std::set<match<T, U>> merge_matches(const std::set<match<T, U>>& v1, const std::set<match<T, U>>& v2) {
		if (v1.empty()) return v2;
		if (v2.empty()) return v1;

		std::set<match<T, U>> rslt;

		//Merge
		for (auto i : v1) {
			for (auto&& j : v2) {
				i.insert(j.begin(), j.end());

				rslt.emplace(i);
			}
		}

		return rslt;
	}
}

template<class T>
puff<T>::puff(const graph<T>& gr, std::size_t max_depth) {
	if (max_depth == 0) throw std::invalid_argument("max_depth must be at least 1");
	sectors.reserve(std::min(max_depth, gr.size()));

	// Build level 1
	sectors.emplace_back();
	for (auto& nd : gr.nodes()) {
		sectors.front().emplace_back(nd);
	}

	std::cout << "1";

	// Build level 2, if needed
	if (max_depth > 1) {
		// Create 2 levels, each holding same sectors but produced from
		// different children. In the end, two levels will be merged.
		level_type new_level1;
		level_type new_level2;

		// For each cluster in first level
		for (auto& cluster : sectors.front()) {
			// Check edges
			const node<T>& only_node = (**cluster.nodes.begin());

			for (auto& adjacent : only_node.adjacent_nodes()) {
				// Based on edges id emplace in one of vectors
				if (adjacent.id() > only_node.id())
					new_level1.emplace_back(cluster, adjacent);
				else
					new_level2.emplace_back(cluster, adjacent);
			}
		}

		// If vectors are empty, no level to build
		if (new_level1.empty()) return;

		// Sort and merge sectors
		std::sort(new_level1.begin(), new_level1.end());
		std::sort(new_level2.begin(), new_level2.end());

		GS_ASSERT(new_level1.size() == new_level2.size());
		for (typename level_type::iterator
			it1 = new_level1.begin(),
			it2 = new_level2.begin();
			it1 != new_level1.end(); ++it1, ++it2) {
			it1->join_children(*it2);
		}

		sectors.emplace_back(std::move(new_level1));
	}

	std::cout << " 2";

	// Build remaining levels using already built ones
	level_builder<T> lb;
	for (std::size_t level = 2; level < max_depth; level++) {
		//std::cout << "level " << level << " growth" << std::endl;
		if (!lb.build(sectors.back())) break;

		// Insert new level in the end
		sectors.emplace(sectors.end(),
			std::move_iterator(lb.result().begin()),
			std::move_iterator(lb.result().end()));
		
		std::cout << " " << level+1;
	}

	std::cout << "\n";

	//std::cout << "Built a puff (max_depth: " << max_depth << ", levels: " << sectors.size() << ", depth at back(): " << sectors.back().size() << "): " << *this;
}

template<class T>
std::size_t puff<T>::depth() const noexcept {
	return sectors.size();
}

template<class T>
std::size_t puff<T>::count_edges() const noexcept {
	std::size_t rslt = 0;

	for (auto i : sectors) {
		for (auto j : i) {
			rslt += j.children.size();
		}
	}

	return rslt;
}

template<class T>
std::size_t puff<T>::count_sectors() const noexcept {
	std::size_t rslt = 0;

	for (auto i : sectors) rslt += i.size();

	return rslt;
}

template<class T>
std::size_t puff<T>::size_in_bytes() const noexcept {
	std::size_t rslt = 0;

	for (auto&& i : sectors) {
		for (auto&& j : i) {
			rslt += j.size_in_bytes();
		}
	}

	return rslt;
}

template<class T>
template<class U, class F>
std::set<match<T, U>> puff<T>::search(const puff<U>& other, F&& compare) const {
	using matches = std::set<match<T, U>>;

	if (other.depth() > depth()) {
		return {};
	}

	matches rslt;

	for (auto&& i : other.sectors[other.depth() - 1]) {
		matches matches_of_one;

		std::vector<std::future<match<T, U>>> future_matches;
		for (auto&& j : sectors[other.depth() - 1]) {
			future_matches.push_back(
				std::move(
					std::async(
						std::launch::async,
						[&j, &i, &compare]() {
							return j.search(i, compare);
						}
					)
				)
			);
		}

		for (auto&& j : future_matches) {
			match<T, U> m(std::move(j.get()));
			if (!m.empty()) matches_of_one.emplace(m);
		}

		if (matches_of_one.empty()) return {};
		rslt = merge_matches(rslt, matches_of_one);
	}

	return rslt;
}

template<class T>
const typename puff<T>::level_type&
puff<T>::operator[](std::size_t idx) const {
	return sectors[idx];
}

template<class T>
bool operator==(const puff<T>& lhs, const puff<T>& rhs) {
	return
		!lhs.search(rhs).empty() &&
		!rhs.search(lhs).empty();
}

template<class T>
bool operator!=(const puff<T>& lhs, const puff<T>& rhs) {
	return !(lhs == rhs);
}

template <class T>
std::ostream& operator<<(std::ostream& os, const puff<T>& obj) {
	os << "{" << std::endl;

	for (std::size_t level = obj.depth() - 1; level != 0; level--) {
		std::cout << "    level " << level << " {" << std::endl;

		for (const auto& i : obj[level]) {
			os << "        " << i << " <= ";
			for (const auto& j : i.children) os << *j << " ";
			os << std::endl;
		}

		std::cout << "    }" << std::endl;
	}

	os << "}";

	return os;
}

} // namespace zh