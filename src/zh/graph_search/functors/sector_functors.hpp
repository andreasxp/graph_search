#pragma once
#include <algorithm>

namespace zh {

template <class T>
class cluster;

template<class T>
struct sector_lexicographical_order {
	bool operator() (cluster<T> const& lhs, cluster<T> const& rhs) const;
	bool operator() (const cluster<T>* const& lhs, const cluster<T>* const& rhs) const;
};

template<class T>
struct sector_nodes_hash {
	std::size_t operator()(const cluster<T>& obj) const;
};

template<class T>
struct sector_nodes_equal {
	std::size_t operator()(const cluster<T>& lhs, const cluster<T>& rhs) const;
};

} // namespace zh

#include "sector_functors.inl"