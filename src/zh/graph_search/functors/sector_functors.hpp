#pragma once
#include <algorithm>

namespace zh {

template <class T, class E>
class cluster;

template<class T, class E>
struct sector_lexicographical_order {
	bool operator() (cluster<T, E> const& lhs, cluster<T, E> const& rhs) const;
	bool operator() (const cluster<T, E>* const& lhs, const cluster<T, E>* const& rhs) const;
};

template<class T, class E>
struct sector_nodes_hash {
	std::size_t operator()(const cluster<T, E>& obj) const;
};

template<class T, class E>
struct sector_nodes_equal {
	std::size_t operator()(const cluster<T, E>& lhs, const cluster<T, E>& rhs) const;
};

} // namespace zh

#include "sector_functors.inl"