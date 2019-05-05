#pragma once
#include "functors.hpp"
#include "connection.hpp"

namespace zh {

template <class T, class E, class NodeHash>
struct connection_node_hash : private NodeHash {
	std::size_t operator()(const connection<T, E>& con) const noexcept(
		noexcept(std::declval<NodeHash>()(*con))) {
		return NodeHash::operator()(*con);
	}
};

template <class T, class E, class NodeEqual>
struct connection_node_equal : private NodeEqual {
	bool operator()(const connection<T, E>& lhs, const connection<T, E>& rhs) const noexcept(
		noexcept(std::declval<NodeEqual>()(*lhs, *rhs))) {
		return NodeEqual::operator()(*lhs, *rhs);
	}
};

} // namespace zh