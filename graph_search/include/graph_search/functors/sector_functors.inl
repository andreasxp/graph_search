#pragma once
#include "sector_functors.hpp"
#include "../node_group.hpp"

template<class T>
inline bool sector_lexicographical_order<T>::operator()(sector<T> const & lhs, sector<T> const & rhs) const {
	return std::lexicographical_compare(
		lhs.nodes.begin(), lhs.nodes.end(),
		rhs.nodes.begin(), rhs.nodes.end(),
		node_value_order<T>());
}

template<class T>
inline bool sector_lexicographical_order<T>::operator()(const sector<T>* const & lhs, const sector<T>* const & rhs) const {
	return operator()(*lhs, *rhs);
}

template<class T>
std::size_t sector_nodes_hash<T>::operator()(const sector<T>& obj) const {
	return std::hash<node_group<T>>()(obj.nodes);
}

template<class T>
inline std::size_t sector_nodes_equal<T>::operator()(const sector<T>& lhs, const sector<T>& rhs) const {
	return lhs.nodes == rhs.nodes;
}
