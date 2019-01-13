#pragma once
#include "graph.hpp"

#include "deps/ska/unordered_map.hpp"
#include "util/assert.hpp"
#include "node/pseudonode.hpp"

template<class T>
inline typename graph<T>::node_iterator 
graph<T>::find(typename node<T>::id_type id) {
	// If an id of 0 was passed, that usually means that it was aquired from
	// dereferencing a node<T>::node_iterator that was equal to end().
	// Such action results in undefined behaviour.
	GS_ASSERT(id != 0);

	pseudonode<T> key(id);
	auto got = m_nodes.find(key.imitator());

	return node_iterator(got);
}

template<class T>
inline typename graph<T>::const_node_iterator 
graph<T>::find(typename node<T>::id_type id) const {
	// If an id of 0 was passed, that usually means that it was aquired from
	// dereferencing a node<T>::node_iterator that was equal to end().
	// Such action results in undefined behaviour.
	GS_ASSERT(id != 0);

	pseudonode<T> key(id);
	auto got = m_nodes.find(key.imitator());

	/*std::cout << "Looking for " << id << " in:\n";
	for (auto&& nd : nodes()) {
		std::cout << "    " << nd.id() << "\n";
	}
	std::cout << "Answer: " <<
		(got == m_nodes.end() ? "not found" : "found") << std::endl;*/


	return const_node_iterator(got);
}

template<class T>
inline graph<T>::graph(const graph& other) {
	// Reserve size for perfomance and to prevent iterator/pointer invalidation
	m_nodes.reserve(other.m_nodes.size());

	// Match other's ptr to node to equivalent ptr in this
	ska::unordered_map<const node<T>*, node<T>*> ptr_match;

	// Emplacing all m_nodes (not connecting)
	for (auto& nd : other) {
		emplace(nd.value());
		ptr_match[&nd] = &m_nodes.back();
	}

	// Connect all m_nodes by looking at other's edges and transforming pointers
	for (auto& nd : other) {
		for (auto& edge_ptr : nd.edges()) {
			connect(
				*ptr_match[&nd],
				*ptr_match[edge_ptr]
			);
		}
	}
}

template<class T>
inline graph<T>::graph(graph&& other) noexcept :
	graph() {
	swap(*this, other);
}

template<class T>
inline graph<T>& graph<T>::operator=(graph<T> other) {
	swap(*this, other);
	return *this;
}

template <class T_>
inline void swap(graph<T_>& lhs, graph<T_>& rhs) noexcept {
	// enable ADL
	using std::swap;

	swap(lhs.m_nodes, rhs.m_nodes);
}

// =============================================================================

template<class T>
inline typename graph<T>::iterator graph<T>::begin() noexcept {
	return iterator(m_nodes.begin());
}

template<class T>
inline typename graph<T>::const_iterator graph<T>::begin() const noexcept {
	return const_iterator(m_nodes.begin());
}

template<class T>
inline typename graph<T>::const_iterator graph<T>::cbegin() const noexcept {
	return const_iterator(m_nodes.cbegin());
}

template<class T>
inline typename graph<T>::iterator graph<T>::end() noexcept {
	return iterator(m_nodes.end());
}

template<class T>
inline typename graph<T>::const_iterator graph<T>::end() const noexcept {
	return const_iterator(m_nodes.end());
}

template<class T>
inline typename graph<T>::const_iterator graph<T>::cend() const noexcept {
	return const_iterator(m_nodes.cend());
}

template<class T>
inline typename graph<T>::nodes_view 
graph<T>::nodes() noexcept {
	return nodes_view(m_nodes);
}

template<class T>
inline typename graph<T>::const_nodes_view 
graph<T>::nodes() const noexcept {
	return const_nodes_view(m_nodes);
}

template<class T>
inline typename graph<T>::node_iterator 
graph<T>::to_node_iterator(typename node<T>::node_iterator iter) noexcept {
	return find(iter->id());
}

template<class T>
inline typename graph<T>::const_node_iterator 
graph<T>::to_node_iterator(typename node<T>::const_node_iterator iter) const noexcept {
	return find(iter->id());
}

template<class T>
inline void graph<T>::connect(node<T>& n1, node<T>& n2) {
	if (n1.id() == n2.id()) throw std::invalid_argument("graph::connect: cannot connect node to itself");
	n1.bi_connect(n2);
}

template<class T>
inline void graph<T>::connect(iterator it1, iterator it2) {
	connect(node_iterator(it1), node_iterator(it2));
}

template<class T>
inline void graph<T>::connect(node_iterator it1, node_iterator it2) {
	connect(*it1, *it2);
}

template<class T>
inline void graph<T>::disconnect(node<T>& n1, node<T>& n2) {
	n1.bi_disconnect(n2);
}

template<class T>
inline void graph<T>::disconnect(iterator it1, iterator it2) {
	disconnect(node_iterator(it1), node_iterator(it2));
}

template<class T>
inline void graph<T>::disconnect(node_iterator it1, node_iterator it2) {
	disconnect(*it1, *it2);
}

template<class T>
inline typename graph<T>::reference graph<T>::front() {
	return *begin();
}

template<class T>
inline typename graph<T>::const_reference graph<T>::front() const {
	return *begin();
}

template<class T>
inline typename graph<T>::reference graph<T>::back() {
	return *std::prev(end());
}

template<class T>
inline typename graph<T>::const_reference graph<T>::back() const {
	return *std::prev(end());
}

template<class T>
inline typename graph<T>::iterator graph<T>::insert(const T& val) {
	return m_nodes.emplace_back(val);
}

template<class T>
inline typename graph<T>::iterator graph<T>::insert(T&& val) {
	return m_nodes.emplace_back(std::move(val));
}

template<class T>
template<class InputIt>
void graph<T>::insert(InputIt first, InputIt last) {
	for (InputIt it = first; it != last; ++it) {
		insert(*it);
	}
}

template<class T>
inline void graph<T>::insert(std::initializer_list<value_type> ilist) {
	insert(ilist.begin(), ilist.end());
}

template<class T>
template<class... Args>
inline typename graph<T>::iterator graph<T>::emplace(Args&&... args) {
	return iterator(m_nodes.emplace(std::forward<Args>(args)...)
		.first);
}

template<class T>
inline typename graph<T>::iterator 
graph<T>::erase(iterator it) {
	return iterator(m_nodes.erase(node_iterator(it)));
}

template<class T>
inline typename graph<T>::node_iterator 
graph<T>::erase(node_iterator it) {
	GS_ASSERT(it != nodes().end());

	for (auto& nd : it->adjacent_nodes()) {
		// Remove all connections other nodes have to this node
		nd.fw_disconnect(*it);
	}

	return node_iterator(m_nodes.erase(it.get_iterator()));
}

template<class T>
inline bool graph<T>::empty() const noexcept {
	return m_nodes.empty();
}

template<class T>
inline void graph<T>::clear() noexcept {
	m_nodes.clear();
}

template<class T>
inline void graph<T>::reserve(size_type new_size) {
	m_nodes.reserve(new_size);
}

template<class T>
inline std::size_t graph<T>::count_edges() const noexcept {
	std::size_t rslt = 0;

	for (auto&& i : m_nodes) {
		rslt += i.second.edges().size();
	}
	rslt /= 2;

	return rslt;
}

template<class T>
inline double graph<T>::ratio() const noexcept {
	std::size_t max_edges = size() * (size() - 1) / 2;
	std::size_t edges = count_edges();

	return static_cast<double>(edges) / max_edges;
}

template<class T>
inline std::size_t graph<T>::size() const noexcept {
	return m_nodes.size();
}

template <class T>
std::ostream& operator<<(std::ostream& os, const graph<T>& obj) {
	os << "{" << std::endl;

	for (auto& nd : obj.nodes()) {
		os << "    " << nd;
		if (!nd.adjacent_nodes().empty()) os << " -> ";

		for (auto& connection : nd.adjacent_nodes()) {
			os << connection << " ";
		}

		os << std::endl;
	}

	os << "}";

	return os;
}

template <class T>
void to_json(json& j, const graph<T>& obj) {
	for (auto&& nd : obj.nodes()) {
		json temp;
		temp["value"] = nd.value();
		temp["id"] = nd.id();
		
		temp["edges"] = json::array();
		for (auto&& adjacent : nd.adjacent_nodes()) {
			temp["edges"].push_back(adjacent.id());
		}

		j.push_back(temp);
	}
}

template <class T>
void from_json(const json& j, graph<T>& obj) {
	using node_iterator = typename graph<T>::node_iterator;

	// Clearing
	obj.clear();
	// Reserve size for perfomance and to prevent iterator/pointer invalidation
	obj.reserve(j.size());

	// Match other's id to node to equivalent ptr in this
	ska::unordered_map<std::size_t, node_iterator> ptr_match;

	// Emplacing all m_nodes (not connecting)
	for (auto& nd : j) {
		auto it = obj.emplace(nd["value"].get<T>());
		ptr_match[nd["id"]] = node_iterator(it);
	}

	// Connect all m_nodes by looking at j's ids and transforming pointers
	for (auto& nd : j) {
		for (auto& edge_id : nd["edges"]) {
			obj.connect(
				ptr_match[nd["id"]],
				ptr_match[edge_id]
			);
		}
	}
}