#pragma once
#include "graph.hpp"
#include "edge/edge.hpp"

namespace zh {

// Constructors ===============================================================
template<class T, class E>
graph<T, E>::graph(const graph& other) {
	m_nodes.reserve(other.size());

	// Convert other node's ptr to new ptr
	ska::flat_hash_map<const node<T, E>*, node<T, E>*> ptr_match;

	// Emplacing all nodes without connecting ---------------------------------
	for (auto& n : other.nodes()) {
		// Emplace nodes and add them to the converter
		ptr_match[&n] = &*emplace(n.value());
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

template<class T, class E>
graph<T, E>::graph(graph&& other) noexcept {
	swap(*this, other);
}

template<class T, class E>
graph<T, E>& graph<T, E>::operator=(graph rhs) {
	swap(*this, rhs);
	return *this;
}

// Iterators ==================================================================
template<class T, class E>
graph_iterator<T, E> graph<T, E>::begin() noexcept {
	return iterator(m_nodes.begin());
}

template<class T, class E>
graph_const_iterator<T, E> graph<T, E>::begin() const noexcept {
	return const_iterator(m_nodes.begin());
}

template<class T, class E>
graph_const_iterator<T, E> graph<T, E>::cbegin() const noexcept {
	return const_iterator(m_nodes.cbegin());
}

template<class T, class E>
graph_iterator<T, E> graph<T, E>::end() noexcept {
	return iterator(m_nodes.end());
}

template<class T, class E>
graph_const_iterator<T, E> graph<T, E>::end() const noexcept {
	return const_iterator(m_nodes.end());
}

template<class T, class E>
graph_const_iterator<T, E> graph<T, E>::cend() const noexcept {
	return const_iterator(m_nodes.cend());
}

template<class T, class E>
graph_nodes_view<T, E> graph<T, E>::nodes() noexcept {
	return nodes_view(m_nodes);
}

template<class T, class E>
graph_const_nodes_view<T, E> graph<T, E>::nodes() const noexcept {
	return const_nodes_view(m_nodes);
}

template<class T, class E>
graph_edges_view<T, E> graph<T, E>::edges() noexcept {
	return edges_view(m_nodes);
}

template<class T, class E>
graph_const_edges_view<T, E> graph<T, E>::edges() const noexcept {
	return const_edges_view(m_nodes);
}

// Connecting =================================================================
template<class T, class E>
template<class ...Args>
void graph<T, E>::connect(node<T, E>& nd1, node<T, E>& nd2, Args&&... edge_args) {
	if constexpr (std::is_same_v<E, void>) {
		static_assert(sizeof...(Args) == 0,
			"graph::connect: arguments for constructing edge_value_type were provided, but edge_value_type is void");
	}
	else {
		static_assert(std::is_constructible_v<E, Args&&...>,
			"graph::connect: cannot constuct edge_value_type from these arguments");
	}

	if (nd1.id() == nd2.id()) {
		throw std::invalid_argument("graph::connect: cannot connect node to itself");
	}

	nd1.connect(nd2, std::forward<Args>(edge_args)...);
}

template<class T, class E>
template<class ...Args>
void graph<T, E>::connect(iterator it1, iterator it2, Args&&... edge_args) {
	connect(node_iterator(it1), node_iterator(it2), std::forward<Args>(edge_args)...);
}

template<class T, class E>
template<class ...Args>
void graph<T, E>::connect(node_iterator it1, node_iterator it2, Args&&... edge_args) {
	connect(*it1, *it2, std::forward<Args>(edge_args)...);
}

template<class T, class E>
void graph<T, E>::disconnect(node<T, E>& n1, node<T, E>& n2) {
	n1.disconnect(n2);
}

template<class T, class E>
void graph<T, E>::disconnect(iterator it1, iterator it2) {
	disconnect(node_iterator(it1), node_iterator(it2));
}

template<class T, class E>
void graph<T, E>::disconnect(node_iterator it1, node_iterator it2) {
	disconnect(*it1, *it2);
}

template<class T, class E>
T& graph<T, E>::front() {
	return *begin();
}

template<class T, class E>
const T& graph<T, E>::front() const {
	return *begin();
}

template<class T, class E>
T& graph<T, E>::back() {
	return *std::prev(end());
}

template<class T, class E>
const T& graph<T, E>::back() const {
	return *std::prev(end());
}

// Modifiers ==================================================================
template<class T, class E>
typename graph<T, E>::node_iterator graph<T, E>::insert(const T& val) {
	return emplace(val);
}

template<class T, class E>
typename graph<T, E>::node_iterator graph<T, E>::insert(T&& val) {
	return emplace(std::move(val));
}

template<class T, class E>
template<class InputIt>
void graph<T, E>::insert(InputIt first, InputIt last) {
	for (; first != last; ++first) {
		emplace(*first);
	}
}

template<class T, class E>
void graph<T, E>::insert(std::initializer_list<value_type> ilist) {
	insert(ilist.begin(), ilist.end());
}

template<class T, class E>
template<class ...Args>
typename graph<T, E>::node_iterator graph<T, E>::emplace(Args&&... args) {
	static_assert(std::is_constructible_v<T, Args&&...>,
		"graph::emplace: cannot constuct value_type from these arguments");

	m_nodes.emplace_back(
		std::make_unique<node<T, E>>(std::forward<Args>(args)...));


	return std::prev(nodes().end());
}

template<class T, class E>
typename graph<T, E>::iterator graph<T, E>::erase(iterator it) {
	return iterator(m_nodes.erase(it.base()));
}

template<class T, class E>
typename graph<T, E>::node_iterator graph<T, E>::erase(node_iterator it) {
	return node_iterator(m_nodes.erase(it.base()));
}

template<class T, class E>
void graph<T, E>::erase(edge<T, E> e) {
	disconnect(e.first(), e.second());
}

template<class T, class E>
void graph<T, E>::clear() noexcept {
	m_nodes.clear();
}

template<class T, class E>
void graph<T, E>::reserve(size_type new_size) {
	m_nodes.reserve(new_size);
}

// Observers ==================================================================
template<class T, class E>
bool graph<T, E>::empty() const noexcept {
	return m_nodes.empty();
}

template<class T, class E>
std::size_t graph<T, E>::size() const noexcept {
	return m_nodes.size();
}

template<class T, class E>
std::size_t graph<T, E>::capacity() const noexcept {
	return m_nodes.capacity();
}

template<class T, class E>
std::size_t graph<T, E>::count_edges() const noexcept {
	return edges().size();
}

template<class T, class E>
double graph<T, E>::ratio() const noexcept {
	std::size_t max_edges = size() * (size() - 1) / 2;
	std::size_t edges = count_edges();

	return static_cast<double>(edges) / max_edges;
}

} // namespace zh