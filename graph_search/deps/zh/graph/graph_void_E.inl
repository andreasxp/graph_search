#pragma once
#include "graph_void_E.hpp"
#include "edge/edge.hpp"

namespace zh {

// Constructors ===============================================================
template<class E>
graph<void, E>::graph(const graph& other) {
	m_nodes.reserve(other.size());

	// Convert other node's ptr to new ptr
	ska::flat_hash_map<const node<void, E>*, node<void, E>*> ptr_match;

	// Emplacing all nodes without connecting ---------------------------------
	for (auto& n : other.nodes()) {
		// Emplace nodes and add them to the converter
		ptr_match[&n] = &*emplace();
	}

	// Connecting all nodes ---------------------------------------------------
	for (auto& e : other.edges()) {
		if (e.first().id() < e.second().id()) {
			if constexpr (std::is_same_v<E, void>) {
				connect(*ptr_match[&e.first()], *ptr_match[&e.second()]);
			}
			else {
				connect(*ptr_match[&e.first()], *ptr_match[&e.second()], e.value());
			}
		}
	}
}

template<class E>
graph<void, E>::graph(graph&& other) noexcept {
	swap(*this, other);
}

template<class E>
graph<void, E>& graph<void, E>::operator=(graph rhs) {
	swap(*this, rhs);
	return *this;
}

// Iterators ==================================================================
template<class E>
graph_nodes_view<void, E> graph<void, E>::nodes() noexcept {
	return nodes_view(m_nodes);
}

template<class E>
graph_const_nodes_view<void, E> graph<void, E>::nodes() const noexcept {
	return const_nodes_view(m_nodes);
}

template<class E>
graph_edges_view<void, E> graph<void, E>::edges() noexcept {
	return edges_view(m_nodes);
}

template<class E>
graph_const_edges_view<void, E> graph<void, E>::edges() const noexcept {
	return const_edges_view(m_nodes);
}

// Connecting =================================================================
template<class E>
template<class ...Args>
void graph<void, E>::connect(node<void, E>& nd1, node<void, E>& nd2, Args&&... edge_args) {
	if constexpr (std::is_same_v<E, void>) {
		static_assert(sizeof...(Args) == 0,
			"graph::connect: arguments for constructing edge_value_type were provided, but edge_value_type is void");
	}
	else {
		static_assert(std::is_constructible_v<E, Args&&...>,
			"graph::connect: cannot constuct edge_value_type from these arguments");
	}

	nd1.connect(nd2, std::forward<Args>(edge_args)...);
}

template<class E>
template<class ...Args>
void graph<void, E>::connect(node_iterator it1, node_iterator it2, Args&&... edge_args) {
	connect(*it1, *it2, std::forward<Args>(edge_args)...);
}

template<class E>
void graph<void, E>::disconnect(node<void, E>& n1, node<void, E>& n2) {
	n1.disconnect(n2);
}

template<class E>
void graph<void, E>::disconnect(node_iterator it1, node_iterator it2) {
	disconnect(*it1, *it2);
}

// Modifiers ==================================================================
template<class E>
typename graph<void, E>::node_iterator graph<void, E>::insert() {
	return emplace();
}

template<class E>
typename graph<void, E>::node_iterator graph<void, E>::emplace() {
	m_nodes.emplace_back(std::make_unique<node<void, E>>());

	return std::prev(nodes().end());
}

template<class E>
typename graph<void, E>::node_iterator graph<void, E>::erase(node_iterator it) {
	return node_iterator(m_nodes.erase(it.base()));
}

template<class E>
void graph<void, E>::erase(edge<void, E> e) {
	disconnect(e.first(), e.second());
}

template<class E>
void graph<void, E>::clear() noexcept {
	m_nodes.clear();
}

template<class E>
void graph<void, E>::reserve(size_type new_size) {
	m_nodes.reserve(new_size);
}

// Observers ==================================================================
template<class E>
bool graph<void, E>::empty() const noexcept {
	return m_nodes.empty();
}

template<class E>
std::size_t graph<void, E>::size() const noexcept {
	return m_nodes.size();
}

template<class E>
std::size_t graph<void, E>::capacity() const noexcept {
	return m_nodes.capacity();
}

template<class E>
std::size_t graph<void, E>::count_edges() const noexcept {
	return edges().size();
}

template<class E>
double graph<void, E>::ratio() const noexcept {
	std::size_t max_edges = size() * (size() - 1) / 2;
	std::size_t edges = count_edges();

	return static_cast<double>(edges) / max_edges;
}

} // namespace zh