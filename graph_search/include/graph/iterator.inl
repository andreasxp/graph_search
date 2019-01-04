#pragma once
#include "iterator.hpp"
#include "node_iterator.hpp"

template <class T>
inline graph<T>::iterator::iterator(const container_iterator& other)
	: base(other) {
}

template <class T>
inline graph<T>::iterator::iterator(const node_iterator& other)
	: base(other.get_iterator()) {
}