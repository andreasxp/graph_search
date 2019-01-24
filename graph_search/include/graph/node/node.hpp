#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <iostream>
#include <utility>

#include "deps/ska/flat_hash_map.hpp"
#include "deps/json.hpp"
using json = nlohmann::json;

#include "../connection/connection.hpp"
#include "../connection/connection_functors.hpp"
#include "node_functors.hpp"

template <class T>
class graph;

template <class T>
class node {
public:
	// Public types ============================================================
	using id_type = std::size_t;

private:
	// Private members and types -----------------------------------------------
	using container = ska::flat_hash_set<
		connection<T>, 
		connection_node_hash<T>, 
		connection_node_equal<T, void, node_id_equal<T>>>;
	using container_iterator       = typename container::iterator;
	using const_container_iterator = typename container::const_iterator;

	std::unique_ptr<T> m_value;
	container m_edges;

	node(T* adopt_ptr = nullptr, container edges = container());

public:
	// Public types (cont.) ====================================================
	class node_iterator;
	class const_node_iterator;

	class nodes_view;
	class const_nodes_view;

	// Constructors ------------------------------------------------------------
	template <class... Args, class = std::enable_if_t<std::is_constructible_v<T, Args&&...>>>
	node(Args&&... args);

	node() = delete;
	node(const node&) = delete;
	node(node&&) = default;

	node& operator=(const node&) = delete;
	node& operator=(node&&) = default;

	// Disconnecting edges is not the node's responsibility.
	// Graph does that when erasing the node.
	~node() = default;

	// Iterators ---------------------------------------------------------------
	nodes_view adjacent_nodes() noexcept;
	const_nodes_view adjacent_nodes() const noexcept;

	// Observers ---------------------------------------------------------------
	id_type id() const noexcept;

	// Member access -----------------------------------------------------------
	T& value();
	const T& value() const;

	// Friends -----------------------------------------------------------------
	template <class T_>
	friend class graph;

	// see pseudonode.hpp
	template <class T_>
	friend class pseudonode;

private:
	// Connecting --------------------------------------------------------------

	// Connectors take mutable references because a node holds pointers to
	// mutable nodes.
	void fw_connect(node& n); //one-way connecting
	void bi_connect(node& n); //two-way connecting

	void fw_disconnect(node& n);
	void bi_disconnect(node& n);
};

template <class T>
std::ostream& operator<<(std::ostream& os, const node<T>& obj);

namespace std {

template <class T>
struct hash<node<T>>;

}

#include "node_iterator.hpp"
#include "nodes_view.hpp"

#include "node.inl"