#pragma once
#include <iostream>
#include "deps/ska/flat_hash_map.hpp"
#include <unordered_map>
#include "../graph.hpp"

namespace zh {

template <class T, class E>
graph<E, T> line_graph(const graph<T, E>& gr) {
	graph<E, T> result;
	result.reserve(gr.count_edges());

	//ska::flat_hash_map<edge<T, E>, node<E, T>*> edge_to_ptr;
	std::unordered_map<const_edge<T, E>, node<E, T>*> edge_to_ptr;

	for (auto&& e : gr.edges()) {
		if constexpr (std::is_same_v<E, void>) {
			edge_to_ptr[e] = &*result.emplace();
		}
		else {
			edge_to_ptr[e] = &*result.emplace(e.value());
		}
	}

	for (auto&& nd : gr.nodes()) {
		for (auto&& e1 : nd.edges()) {
			for (auto&& e2 : nd.edges()) {
				if (e1 != e2) {
					if constexpr (std::is_same_v<T, void>) {
						result.connect(
							*edge_to_ptr[e1],
							*edge_to_ptr[e2]
						);
					}
					else {
						result.connect(
							*edge_to_ptr[e1],
							*edge_to_ptr[e2],
							nd.value()
						);
					}
				}
			}
		}
	}

	return result;
}

} // namespace zh