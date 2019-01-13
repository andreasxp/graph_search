#pragma once
#include "node_iterator.hpp"

template <class T>
inline node<T>::node_iterator::node_iterator(
	const container_iterator& other) : 
	base(other) {
}

template <class T>
inline node<T>::const_node_iterator::const_node_iterator(
	const node_iterator& other)	: 
	base(other.get_iterator()) {
}

template <class T>
inline node<T>::const_node_iterator::const_node_iterator(
	const const_container_iterator& other) :
	base(other) {
}
