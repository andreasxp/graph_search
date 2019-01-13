#pragma once
#include <cstdint>
#include <iostream>

#include "deps/ska/unordered_map.hpp"
#include "deps/json.hpp"
using json = nlohmann::json;

#include "node/node_functors.hpp"
#include "node/node.hpp"

#include <unordered_set>

template <class T>
class graph {
private:
	using container = ska::unordered_set<node<T>, std::hash<node<T>>, node_id_equal<T>>;
	
	using container_iterator = typename container::iterator;
	using const_container_iterator = typename container::const_iterator;

	container m_nodes;

public:
	// Member types ============================================================
	using value_type      = T;
	using size_type       = typename container::size_type;
	using difference_type = typename container::difference_type;
	using allocator_type  = typename container::allocator_type;
	using reference       = typename container::reference;
	using const_reference = typename container::const_reference;
	using pointer         = typename container::pointer;
	using const_pointer   = typename container::const_pointer;

	// The followingg iterators and views are implemented as nested classes for
	// different reasons:
	// 1. More straightforward casting between iterators
	// 2. Can't forward-declare using directives
	// 3. Clearer error messages without using directives

	// Iterate over values
	class iterator;
	class const_iterator;

	// Iterate over nodes
	class node_iterator;
	class const_node_iterator;

	// nodes_view is a container_view - a lightweight struct that provides a
	// way to access elements inside via begin and end. Since there are several
	// ways to iterate over a graph (values, nodes, edges), graph provides
	// nodes_view, edges_view, as well as plain begin/end for values.
	class nodes_view;
	class const_nodes_view;

	// Member functions ========================================================
	// Constructors ------------------------------------------------------------
	constexpr graph() = default;
	graph(const graph& other);
	graph(graph&& other) noexcept;
	~graph() = default;

	graph& operator=(graph rhs);

	template <class T_>
	friend inline void swap(graph<T_>& first, graph<T_>& second) noexcept;

	// Iterators ---------------------------------------------------------------
	iterator       begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	iterator       end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;

	// Node iterators ----------------------------------------------------------
	nodes_view       nodes() noexcept;
	const_nodes_view nodes() const noexcept;

	// Convert node::node_iterator to graph::node_iterator
	node_iterator       to_node_iterator(
		typename node<T>::node_iterator iter) noexcept;
	const_node_iterator to_node_iterator(
		typename node<T>::const_node_iterator iter) const noexcept;

	// Connecting --------------------------------------------------------------

	void connect(node<T>& n1, node<T>& n2);
	void connect(iterator it1, iterator it2);
	void connect(node_iterator it1, node_iterator it2);

	void disconnect(node<T>& n1, node<T>& n2);
	void disconnect(iterator it1, iterator it2);
	void disconnect(node_iterator it1, node_iterator it2);

	// Element access ----------------------------------------------------------
	
	// "Every container has to have a front() and back(). Except maybe 
	//  forward_list, but don't use forward_list"
	//     - andreasxp 2018
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	// Lookup ------------------------------------------------------------------
	node_iterator       find(typename node<T>::id_type id);
	const_node_iterator find(typename node<T>::id_type id) const;

	// Modifiers ---------------------------------------------------------------
	iterator insert(const T& val);
	iterator insert(T&& val);

	template <class InputIt>
	void insert(InputIt first, InputIt last);
	void insert(std::initializer_list<value_type> ilist);

	template <class... Args>
	iterator emplace(Args&&... args);

	iterator erase(iterator it);
	node_iterator erase(node_iterator it);
	void clear() noexcept;

	void reserve(size_type new_size);

	// Observers --------------------------------------------------------------
	bool empty() const noexcept;
	std::size_t size() const noexcept;

	std::size_t count_edges() const noexcept;
	double ratio() const noexcept;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const graph<T>& obj);

template <class T>
void to_json(json& j, const graph<T>& obj);

template <class T>
void from_json(const json& j, graph<T>& obj);

#include "iterator.hpp"
#include "node_iterator.hpp"
#include "nodes_view.hpp"

#include "graph.inl"