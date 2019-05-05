#pragma once
#include <cassert>
#include "node.hpp"

namespace zh {

template<class T, class E>
template<class ...Args>
node<T, E>::node(Args&&... value_args) :
	m_value(std::forward<Args>(value_args)...) {
	static_assert(std::is_constructible_v<T, Args&&...>, "node::node: cannot constuct value_type from these arguments");
}

template<class T, class E>
node_nodes_view<T, E> node<T, E>::adjacent_nodes() noexcept {
	return nodes_view(m_connections);
}

template<class T, class E>
node_const_nodes_view<T, E> node<T, E>::adjacent_nodes() const noexcept {
	return const_nodes_view(m_connections);
}

template<class T, class E>
node_edges_view<T, E> node<T, E>::edges() noexcept {
	return edges_view(m_connections, *this);
}

template<class T, class E>
node_const_edges_view<T, E> node<T, E>::edges() const noexcept {
	return const_edges_view(m_connections, *this);
}

template<class T, class E>
typename node<T, E>::id_type node<T, E>::id() const noexcept {
	return reinterpret_cast<id_type>(this);
}

template<class T, class E>
T& node<T, E>::value() noexcept {
	return m_value;
}

template<class T, class E>
const T& node<T, E>::value() const noexcept {
	return m_value;
}

template<class T, class E>
template<class ...Args>
void node<T, E>::connect(node& n, Args&&... edge_args) {
	if constexpr (std::is_same_v<E, void>) {
		static_assert(sizeof...(Args) == 0, 
			"node::connect: arguments for constructing edge_value_type were provided, but edge_value_type is void");
	}
	else {
		static_assert(std::is_constructible_v<E, Args&&...>, 
			"node::connect: cannot constuct edge_value_type from these arguments");
	}

	// Make 2 connections {*this, n} and {n, *this} with provided arguments
	auto [con1_temp, con2_temp] = make_connections(*this, n, std::forward<Args>(edge_args)...);

	auto& con1 = *  m_connections.insert(std::move(con1_temp)).first; // Create connection 1
	auto& con2 = *n.m_connections.insert(std::move(con2_temp)).first; // Create connection 2

	// If a value was inserted, verify that one of the connections has the deleter.
	// Otherwise there's a bug in this function, the deleter was lost somewhere and
	// the value will be deleted at the end of this scope.
	if constexpr (!std::is_same_v<E, void>) {
		assert(
			con1.value_ptr().has_deleter() ||
			con2.value_ptr().has_deleter()
		);
	}
}

template<class T, class E>
void node<T, E>::disconnect(node& n) {
	  m_connections.erase(connection<T, E>::valueless(n));
	n.m_connections.erase(connection<T, E>::valueless(*this));
}

} // namespace zh