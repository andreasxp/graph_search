#pragma once
#include <cassert>
#include "node_void_E.hpp"

namespace zh {

template<class E>
node_nodes_view<void, E> node<void, E>::adjacent_nodes() noexcept {
	return nodes_view(m_connections);
}

template<class E>
node_const_nodes_view<void, E> node<void, E>::adjacent_nodes() const noexcept {
	return const_nodes_view(m_connections);
}

template<class E>
node_edges_view<void, E> node<void, E>::edges() noexcept {
	return edges_view(m_connections, *this);
}

template<class E>
node_const_edges_view<void, E> node<void, E>::edges() const noexcept {
	return const_edges_view(m_connections, *this);
}

template<class E>
typename node<void, E>::id_type node<void, E>::id() const noexcept {
	return reinterpret_cast<id_type>(this);
}

template<class E>
template<class ...Args>
void node<void, E>::connect(node& n, Args&&... edge_args) {
	if constexpr (std::is_same_v<E, void>) {
		static_assert(sizeof...(Args) == 0, 
			"node::connect: arguments for constructing edge_value_type were provided, but edge_value_type is void");
	}
	else {
		static_assert(std::is_constructible_v<E, Args&&...>, 
			"node::connect: cannot constuct edge_value_type from these arguments");
	}

	// Make 2 connections {*this, n} and {n, *this} with provided arguments
	auto [con1, con2] = make_connections(*this, n, std::forward<Args>(edge_args)...);

	// Create and get a ref to connection 1
	auto& con = *m_connections.insert(std::move(con1)).first;
	// Create connection 2
	n.m_connections.insert(std::move(con2));

	// If a value was inserted, verify that one of the connections has the deleter.
	// Otherwise there's a bug in this function, the deleter was lost somewhere and
	// the value will be deleted at the end of this scope.
	if constexpr (!std::is_same_v<E, void>) {
		assert(con.value_ptr().has_deleter());
	}
}

template<class E>
void node<void, E>::disconnect(node& n) {
	  m_connections.erase(connection<void, E>::valueless(n));
	n.m_connections.erase(connection<void, E>::valueless(*this));
}

}