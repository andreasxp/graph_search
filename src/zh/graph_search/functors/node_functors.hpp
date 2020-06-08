#pragma once
#include <zh/graph.hpp>
// These are node functors, required for puff and cluster

namespace zh {

template<class T, class E>
struct node_value_equal {
	bool operator() (const node<T, E>* const& lhs, const node<T, E>* const& rhs) const;
};

template<class T, class E>
struct node_value_order {
	bool operator() (const node<T, E>* const& lhs, const node<T, E>* const& rhs) const;
};

} // namespace zh

#include "node_functors.inl"