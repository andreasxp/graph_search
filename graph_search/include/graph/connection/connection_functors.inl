#pragma once
#include "connection_functors.hpp"
#include "connection.hpp"

template <class T, class E, class NodeHash>
struct connection_node_hash : private NodeHash {
	std::size_t operator()(const connection<T, E>& con) const noexcept(
		noexcept(NodeHash::operator()(*con))) {
		return NodeHash::operator()(*con);
	}
};

template <class T, class E, class NodeEqual>
struct connection_node_equal : private NodeEqual {
	bool operator()(const connection<T, E>& lhs, const connection<T, E>& rhs) const noexcept(
		noexcept(NodeEqual::operator()(*lhs, *rhs))) {
		return NodeEqual::operator()(*lhs, *rhs);
	}
};