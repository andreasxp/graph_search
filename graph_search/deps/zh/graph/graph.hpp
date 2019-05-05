#pragma once
#include <cstdint>
#include <memory>

#include "deps/ska/unordered_map.hpp"

#include "graph_fwd.hpp"
#include "detail.hpp"
#include "node/node.hpp"
#include "node/functors.hpp"

#include "edges_view.hpp"
#include "iterator.hpp"
#include "nodes_view.hpp"

namespace zh {

template <class T, class E>
class graph {
public:
	using container = detail::graph_container<T, E>;
	container m_nodes;

public:
	// Member types ============================================================
	using value_type      = T;
	using edge_value_type = E;
	using edge_type       = edge<T, E>;
	using node_type       = node<T, E>;

	using size_type       = typename container::size_type;
	using difference_type = typename container::difference_type;

	using reference       = T&;
	using const_reference = const T&;

	using pointer         = T*;
	using const_pointer   = const T*;

	// The following iterators and views are implemented as nested classes for
	// these reasons:
	// 1. More straightforward casting between iterators
	// 2. Can't forward-declare using directives
	// 3. Clearer error messages without using directives

	// nodes_view is a prism - a lightweight struct that provides a
	// way to access elements inside via begin and end. Since there are several
	// ways to iterate over a graph (values, nodes, edges), graph provides
	// nodes_view, edges_view, as well as plain begin/end for values.
	using       nodes_view = graph_nodes_view<T, E>;
	using const_nodes_view = graph_const_nodes_view<T, E>;

	using       edges_view = graph_edges_view<T, E>;
	using const_edges_view = graph_const_edges_view<T, E>;

	// Iterate over values
	using iterator       = graph_iterator<T, E>;
	using const_iterator = graph_const_iterator<T, E>;

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
	iterator       begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	iterator       end() noexcept;
	const_iterator end() const noexcept;
	const_iterator cend() const noexcept;

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
	static void connect(node<T, E>& nd1, node<T, E>& nd2, Args&&... args);
	template <class... Args>
	static void connect(iterator it1, iterator it2, Args&&... args);
	template <class... Args>
	static void connect(node_iterator it1, node_iterator it2, Args&&... args);

	static void disconnect(node<T, E>& nd1, node<T, E>& nd2);
	static void disconnect(iterator it1, iterator it2);
	static void disconnect(node_iterator it1, node_iterator it2);

	// Element access ----------------------------------------------------------

	// "Every container has to have a front() and back(). Except maybe 
	//  forward_list, but don't use forward_list"
	//     - andreasxp 2018
	T&       front();
	const T& front() const;
	T&       back();
	const T& back() const;

	// Modifiers ---------------------------------------------------------------
	node_iterator insert(const T& val);
	node_iterator insert(T&& val);

	template <class InputIt>
	void insert(InputIt first, InputIt last);
	void insert(std::initializer_list<value_type> ilist);

	template <class... Args>
	node_iterator emplace(Args&&... args);

	// Erase nodes
	iterator erase(iterator it);
	node_iterator erase(node_iterator it);
	
	// Erase edges
	void erase(edge<T, E> e);

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

#include "graph_void_E.hpp"
#include "non_member.hpp"

#include "graph.inl"