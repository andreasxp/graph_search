#pragma once

template <class T>
class node;

template<class T>
struct node_value_equal {
	inline bool operator() (const node<T>* const& lhs, const node<T>* const& rhs) const;
};

template<class T>
struct node_value_order {
	inline bool operator() (const node<T>* const& lhs, const node<T>* const& rhs) const;
};

#include "inline/node_functors.inl"