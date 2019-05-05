#pragma once
#include <utility>
#include "../node/node_fwd.hpp"

namespace zh {

// Produces a hash of a connection<T, E> by hashing its node component using
// specified NodeHash. connection's value() does not contribute to the hash.
template <class T, class E = void, class NodeHash = std::hash<node<T, E>>>
struct connection_node_hash;

// Evaluates connection<T, E> equality by comparing its node component using
// specified NodeEqual. connection's value() does not contribute to comparison.
template <class T, class E = void, class NodeEqual = std::equal_to<node<T, E>>>
struct connection_node_equal;

} // namespace zh

#include "functors.inl"