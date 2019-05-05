#pragma once
#include <stdexcept>
#include <future>
#include <iostream>

#include "puff.hpp"
#include "level_builder/level_builder.hpp"
#include "zh/util/assert.hpp"

namespace zh {

template<class T, class E>
puff<T, E>::puff(const graph<T, E>& gr, std::size_t max_depth) {
	if (max_depth == 0) throw std::invalid_argument("max_depth must be at least 1");
	sectors.reserve(std::min(max_depth, gr.size()));

	// Build level 1
	sectors.emplace_back();
	for (auto& nd : gr.nodes()) {
		sectors.front().emplace_back(nd);
	}

	// Build level 2, if needed
	if (max_depth > 1) {
		// Create 2 levels, each holding same sectors but produced from
		// different children. In the end, two levels will be merged.
		level_type new_level1;
		level_type new_level2;

		// For each cluster in first level
		for (auto& cluster : sectors.front()) {
			// Check edges
			const node<T, E>& only_node = (**cluster.nodes.begin());

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

	// Build remaining levels using already built ones
	level_builder<T, E> lb;
	for (std::size_t level = 2; level < max_depth; level++) {
		//std::cout << "level " << level << " growth" << std::endl;
		if (!lb.build(sectors.back())) break;

		// Insert new level in the end
		sectors.emplace(sectors.end(),
			std::move_iterator(lb.result().begin()),
			std::move_iterator(lb.result().end()));
	}

	//std::cout << "Built a puff (max_depth: " << max_depth << ", levels: " << sectors.size() << ", depth at back(): " << sectors.back().size() << "): " << *this;
}

template<class T, class E>
std::size_t puff<T, E>::depth() const noexcept {
	return sectors.size();
}

template<class T, class E>
std::size_t puff<T, E>::count_edges() const noexcept {
	std::size_t rslt = 0;

	for (auto i : sectors) {
		for (auto j : i) {
			rslt += j.children.size();
		}
	}

	return rslt;
}

template<class T, class E>
std::size_t puff<T, E>::count_sectors() const noexcept {
	std::size_t rslt = 0;

	for (auto i : sectors) rslt += i.size();

	return rslt;
}

template<class T, class E>
std::size_t puff<T, E>::size_in_bytes() const noexcept {
	std::size_t rslt = 0;

	for (auto&& i : sectors) {
		for (auto&& j : i) {
			rslt += j.size_in_bytes();
		}
	}

	return rslt;
}

template<class T, class E>
std::set<graph_match> puff<T, E>::search(const puff& other) const {
	if (other.depth() > depth()) {
		return {};
	}

	std::set<graph_match> rslt;

	for (auto&& i : other.sectors[other.depth() - 1]) {
		std::set<graph_match> matches_of_one;

		std::vector<std::future<graph_match>> matches;
		for (auto&& j : sectors[other.depth() - 1]) {
			matches.push_back(std::move(std::async(std::launch::async, &cluster<T, E>::search, &j, std::cref(i))));
		}

		for (auto&& j : matches) {
			graph_match match(std::move(j.get()));
			if (match) matches_of_one.emplace(match);
		}

		if (matches_of_one.empty()) return {};
		rslt = merge(rslt, matches_of_one);
	}

	return rslt;
}

template<class T, class E>
const typename puff<T, E>::level_type&
puff<T, E>::operator[](std::size_t idx) const {
	return sectors[idx];
}

template<class T, class E>
bool operator==(const puff<T, E>& lhs, const puff<T, E>& rhs) {
	return
		!lhs.search(rhs).empty() &&
		!rhs.search(lhs).empty();
}

template<class T, class E>
bool operator!=(const puff<T, E>& lhs, const puff<T, E>& rhs) {
	return !(lhs == rhs);
}

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const puff<T, E>& obj) {
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