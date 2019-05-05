#pragma once
#include "iterator.hpp"
#include "node_iterator.hpp"

namespace zh {

template <class T, class E>
T& graph_iterator<T, E>::dereference() const noexcept {
	return (*this->base_reference())->value();
}

template <class T, class E>
graph_iterator<T, E>::graph_iterator(graph_node_iterator<T, E> other) noexcept :
	base_type(other.base()) {
}

template <class T, class E>
const T& graph_const_iterator<T, E>::dereference() const noexcept {
	return (*this->base_reference())->value();
}

template <class T, class E>
graph_const_iterator<T, E>::graph_const_iterator(graph_iterator<T, E> other) noexcept :
	base_type(other.base()) {
}

template <class T, class E>
graph_const_iterator<T, E>::graph_const_iterator(graph_node_iterator<T, E> other) noexcept :
	base_type(other.base()) {
}

template <class T, class E>
graph_const_iterator<T, E>::graph_const_iterator(graph_const_node_iterator<T, E> other) noexcept :
	base_type(other.base()) {
}

} // namespace zh