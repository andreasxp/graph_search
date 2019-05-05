#pragma once
#include <stdexcept>
#include <string>
#include "mutate.hpp"
#include "util/iterator.hpp"
#include "deps/zh/random.hpp"

namespace zh {

template<class T, class E>
void mutate_nodes(graph<T, E>& gr, std::size_t target_size) {
	if constexpr (!std::is_same_v<T, void>) {
		static_assert(std::is_fundamental_v<T> && std::is_arithmetic_v<T>,
			"mutate_nodes: no default generator available for this type");

		mutate_nodes(gr, target_size, generator<T>());
	}
	else {
		if (target_size > gr.size()) {
			for (std::size_t i = gr.size(); i < target_size; ++i) {
				gr.emplace();
			}
		}
		else {
			for (std::size_t i = gr.size(); i > target_size; --i) {
				auto it = select_from(gr.nodes());
				gr.erase(it);
			}
		}
	}
}

template<class T, class E, class ValueGen>
void mutate_nodes(graph<T, E>& gr, std::size_t target_size, ValueGen&& gen) {
	static_assert(!std::is_same_v<T, void>,
		"mutate_nodes: a generator was provided, but graph's value_type is void");

	static_assert(std::is_constructible_v<T, decltype(gen())>,
		"mutate_nodes: provided generator's output cannot be used to construct graph's value_type");

	if (target_size > gr.size()) {
		for (std::size_t i = gr.size(); i < target_size; ++i) {
			gr.emplace(gen());
		}
	}
	else {
		for (std::size_t i = gr.size(); i > target_size; --i) {
			auto it = select_from(gr.nodes());
			gr.erase(it);
		}
	}
}

template<class T, class E>
void mutate_edges(graph<T, E>& gr, double target_ratio) {
	if (target_ratio > 1 || target_ratio < 0) {
		throw std::invalid_argument(
			"mutate_edges: target_ratio must be in [0, 1], got " + std::to_string(target_ratio));
	}

	if constexpr (!std::is_same_v<E, void>) {
		static_assert(std::is_fundamental_v<E> && std::is_arithmetic_v<E>,
			"mutate_edges: no default generator available for this type");

		mutate_edges(gr, target_ratio, generator<E>());
	}
	else {
		std::size_t max_edges = gr.size() * (gr.size() - 1) / 2;
		std::size_t edges = gr.count_edges();
		std::size_t target_edges = static_cast<std::size_t>(round(target_ratio * max_edges));

		if (target_edges > edges) {
			for (std::size_t i = edges; i < target_edges; ++i) {
				// Step 1: select a node that is not yet connected to every other node
				auto it1 = select_from(gr.nodes());
				while (it1->adjacent_nodes().size() == gr.size() - 1) {
					it1 = select_from(gr.nodes());
				}
				node<T, E>& nd1 = *it1;
				
				// Step 2: select a second node that is:
				// - not connected to the first
				// - not the same as first
				auto it2 = select_from(gr.nodes());
				while (it2->adjacent_nodes().contains(nd1) || it2->id() == nd1.id()) {
					it2 = select_from(gr.nodes());
				}
				node<T, E>& nd2 = *it2;

				// Step 3: connect 2 nodes
				gr.connect(nd1, nd2);
			}
		}
		else {
			for (std::size_t i = edges; i > target_edges; --i) {
				auto it = select_from(gr.edges());
				gr.erase(*it);
			}
		}
	}
}

template<class T, class E, class EdgeGen>
void mutate_edges(graph<T, E>& gr, double target_ratio, EdgeGen&& gen) {
	if (target_ratio > 1 || target_ratio < 0) {
		throw std::invalid_argument(
			"mutate_edges: target_ratio must be in [0, 1], got " + std::to_string(target_ratio));
	}

	static_assert(!std::is_same_v<E, void>,
		"mutate_edges: a generator was provided, but graph's edge_value_type is void");

	static_assert(std::is_constructible_v<E, decltype(gen())>,
		"mutate_edges: provided generator's output cannot be used to construct graph's edge_value_type");

	std::size_t max_edges = gr.size() * (gr.size() - 1) / 2;
	std::size_t edges = gr.count_edges();
	std::size_t target_edges = static_cast<std::size_t>(round(target_ratio * max_edges));

	if (target_edges > edges) {
		for (std::size_t i = edges; i < target_edges; ++i) {
			// Step 1: select a node that is not yet connected to every other node
			auto it1 = select_from(gr.nodes());
			while (it1->adjacent_nodes().size() == gr.size() - 1) {
				it1 = select_from(gr.nodes());
			}
			node<T, E>& nd1 = *it1;

			// Step 2: select a second node that is:
			// - not connected to the first
			// - not the same as first
			auto it2 = select_from(gr.nodes());
			while (it2->adjacent_nodes().contains(nd1) || it2->id() == nd1.id()) {
				it2 = select_from(gr.nodes());
			}
			node<T, E>& nd2 = *it2;

			// Step 3: connect 2 nodes
			gr.connect(nd1, nd2, gen());
		}
	}
	else {
		for (std::size_t i = edges; i > target_edges; --i) {
			auto it = select_from(gr.edges());
			gr.erase(*it);
		}
	}
}

} // namespace zh