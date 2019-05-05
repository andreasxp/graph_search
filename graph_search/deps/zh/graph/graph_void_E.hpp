#pragma once
#include <cstdint>
#include <memory>
#include <iostream>

#include "deps/ska/unordered_map.hpp"

#include "graph_fwd.hpp"
#include "detail.hpp"
#include "node/node.hpp"
#include "node/functors.hpp"

#include "edges_view.hpp"
#include "iterator.hpp"
#include "nodes_view.hpp"

namespace zh {

template <class E>
class graph<void, E> {
private:
	using container = detail::graph_container<void, E>;
	container m_nodes;

public:
	// Member types ============================================================
	using value_type      = void;
	using edge_value_type = E;
	using edge_type       = edge<void, E>;
	using node_type       = node<void, E>;

	using size_type       = typename container::size_type;
	using difference_type = typename container::difference_type;

	// The following iterators and views are implemented as nested classes for
	// these reasons:
	// 1. More straightforward casting between iterators
	// 2. Can't forward-declare using directives
	// 3. Clearer error messages without using directives

	// nodes_view is a prism - a lightweight struct that provides a
	// way to access elements inside via begin and end. Since there are several
	// ways to iterate over a graph (values, nodes, edges), graph provides
	// nodes_view, edges_view, as well as plain begin/end for values.
	using       nodes_view = graph_nodes_view<void, E>;
	using const_nodes_view = graph_const_nodes_view<void, E>;

	using       edges_view = graph_edges_view<void, E>;
	using const_edges_view = graph_const_edges_view<void, E>;

	// Iterate over nodes
	using       node_iterator = typename       nodes_view::iterator;
	using const_node_iterator = typename const_nodes_view::iterator;

	// Iterate over edges
	using       edge_iterator = typename       edges_view::iterator;
	using const_edge_iterator = typename const_edges_view::iterator;

	// Member functions ========================================================
	// Constructors ------------------------------------------------------------
	constexpr graph() = default;
	graph(const graph& other);
	graph(graph&& other) noexcept;
	~graph() = default;

	graph& operator=(graph rhs);

	template <class T_, class E_>
	friend void swap(graph<T_, E_>& first, graph<T_, E_>& second) noexcept;

	// Iterators ---------------------------------------------------------------
	// No iterators in graph<void, E>

	// Node iterators ----------------------------------------------------------
	nodes_view       nodes() noexcept;
	const_nodes_view nodes() const noexcept;

	// Edge iterators ----------------------------------------------------------
	edges_view       edges() noexcept;
	const_edges_view edges() const noexcept;

	// Connecting --------------------------------------------------------------
	// These are all static because it doesn't actually matter, graph just
	// relays the connect request to nodes themselves.
	template <class... Args>
	static void connect(node<void, E>& nd1, node<void, E>& nd2, Args&& ... args);
	template <class... Args>
	static void connect(node_iterator it1, node_iterator it2, Args&& ... args);

	static void disconnect(node<void, E>& nd1, node<void, E>& nd2);
	static void disconnect(node_iterator it1, node_iterator it2);

	// Element access ----------------------------------------------------------
	// No element access in graph<void, E>

	// Modifiers ---------------------------------------------------------------
	node_iterator insert();
	node_iterator emplace();

	node_iterator erase(node_iterator it); // Erase nodes
	void erase(edge<void, E> e);           // Erase edges

	void clear() noexcept;

	void reserve(size_type new_size);

	// Observers --------------------------------------------------------------
	bool empty() const noexcept;
	std::size_t size() const noexcept;
	std::size_t capacity() const noexcept;

	std::size_t count_edges() const noexcept;
	double ratio() const noexcept;
};

} // namespace zh

#include "non_member.hpp"

#include "graph_void_E.inl"