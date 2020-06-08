#pragma once
#include <type_traits>
#include <ska/flat_hash_map.hpp>
#include "json.hpp"

namespace zh {

template <class T, class E>
void from_json(const json& j, graph<T, E>& gr) {
	// Clear and reserve size for perfomance and to prevent iterator/pointer invalidation
	gr.clear();
	gr.reserve(j.size());

	// Match other's id to node to equivalent ptr in this
	ska::flat_hash_map<std::size_t, node<T, E>*> ptr_match;
	ptr_match.reserve(j.size());

	// Emplacing all nodes (not connecting)
	for (auto&& nd : j["nodes"]) {
		node<T, E>* ptr = nullptr;

		if constexpr (std::is_same_v<T, void>) {
			ptr = &*gr.emplace();
		}
		else {
			ptr = &*gr.emplace(nd["value"].get<T>());
		}

		ptr_match[nd["id"]] = ptr;
	}

	// Connect all nodes
	for (auto&& e : j["edges"]) {
		if constexpr (std::is_same_v<E, void>) {
			gr.connect(
				*ptr_match[e["first"]],
				*ptr_match[e["second"]]
			);
		}
		else {
			gr.connect(
				*ptr_match[e["first"]],
				*ptr_match[e["second"]],
				e["value"].get<E>()
			);
		}
	}
}

template <class T, class E>
void to_json(json& j, const graph<T, E>& gr) {
	j = json::object();
	j["nodes"] = json::array();
	j["edges"] = json::array();

	for (auto&& nd : gr.nodes()) {
		json j_node;

		if constexpr (!std::is_same_v<T, void>) {
			j_node["value"] = nd.value();
		}
		j_node["id"] = nd.id();

		j["nodes"].push_back(j_node);
	}

	for (auto&& e : gr.edges()) {
		json j_edge;

		j_edge["first"]  = e.first().id();
		j_edge["second"] = e.second().id();

		if constexpr (!std::is_same_v<E, void>) {
			j_edge["value"] = e.value();
		}

		j["edges"].push_back(j_edge);
	}
}

} // namespace zh