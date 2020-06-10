#pragma once
#include "sector_functors.hpp"
#include "../node_group.hpp"

namespace zh {

template<class T>
bool sector_lexicographical_order<T>::operator()(cluster<T> const& lhs, cluster<T> const& rhs) const {
	return std::lexicographical_compare(
		lhs.nodes.begin(), lhs.nodes.end(),
		rhs.nodes.begin(), rhs.nodes.end(),
		node_value_order<T, void>());
}

template<class T>
bool sector_lexicographical_order<T>::operator()(const cluster<T>* const& lhs, const cluster<T>* const& rhs) const {
	return operator()(*lhs, *rhs);
}

template<class T>
std::size_t sector_nodes_hash<T>::operator()(const cluster<T>& obj) const {
	return std::hash<node_group<T, void>>()(obj.nodes);
}

template<class T>
std::size_t sector_nodes_equal<T>::operator()(const cluster<T>& lhs, const cluster<T>& rhs) const {
	return lhs.nodes == rhs.nodes;
}

} // namespace zh