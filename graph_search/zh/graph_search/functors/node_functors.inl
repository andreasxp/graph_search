#pragma once
#include "node_functors.hpp"

namespace zh {

template<class T, class E>
bool node_value_equal<T, E>::operator()(const node<T, E>* const& lhs, const node<T, E>* const& rhs) const {
	return lhs->value() == rhs->value();
}

template<class T, class E>
bool node_value_order<T, E>::operator()(const node<T, E>* const& lhs, const node<T, E>* const& rhs) const {
	return lhs->value() < rhs->value() ||
		(lhs->value() == rhs->value() && lhs->id() < rhs->id());
}

}