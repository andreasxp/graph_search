#pragma once
#include "node_functors.hpp"
#include "graph.hpp"

template<class T>
inline bool node_value_equal<T>::operator()(const node<T>* const & lhs, const node<T>* const & rhs) const {
	return lhs->value() == rhs->value();
}

template<class T>
inline bool node_value_order<T>::operator()(const node<T>* const & lhs, const node<T>* const & rhs) const {
	return lhs->value() < rhs->value() ||
		(lhs->value() == rhs->value() && lhs->id() < rhs->id());
}