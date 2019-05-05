#pragma once
#include "node_iterator.hpp"
#include "iterator.hpp"

namespace zh {

template <class T, class E>
graph_node_iterator<T, E>::graph_node_iterator(graph_iterator<T, E> other) noexcept :
	base_type(other.base()) {
}

template <class T, class E>
graph_const_node_iterator<T, E>::graph_const_node_iterator(graph_node_iterator<T, E> other) noexcept :
	base_type(other.base()) {
}

template <class T, class E>
graph_const_node_iterator<T, E>::graph_const_node_iterator(graph_iterator<T, E> other) noexcept :
	base_type(other.base()) {
}

template <class T, class E>
graph_const_node_iterator<T, E>::graph_const_node_iterator(graph_const_iterator<T, E> other) noexcept :
	base_type(other.base()) {
}

}