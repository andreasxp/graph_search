#pragma once
#include "node_iterator_void_E.hpp"

namespace zh {

template <class E>
graph_const_node_iterator<void, E>::graph_const_node_iterator(graph_node_iterator<void, E> other) noexcept :
	base_type(other.base()) {
}

}