#pragma once
#include "sector_functors.hpp"
#include "../node_group.hpp"

namespace zh {

template<class T, class E>
bool sector_lexicographical_order<T, E>::operator()(cluster<T, E> const& lhs, cluster<T, E> const& rhs) const {
	return std::lexicographical_compare(
		lhs.nodes.begin(), lhs.nodes.end(),
		rhs.nodes.begin(), rhs.nodes.end(),
		node_value_order<T, E>());
}

template<class T, class E>
bool sector_lexicographical_order<T, E>::operator()(const cluster<T, E>* const& lhs, const cluster<T, E>* const& rhs) const {
	return operator()(*lhs, *rhs);
}

template<class T, class E>
std::size_t sector_nodes_hash<T, E>::operator()(const cluster<T, E>& obj) const {
	return std::hash<node_group<T, E>>()(obj.nodes);
}

template<class T, class E>
std::size_t sector_nodes_equal<T, E>::operator()(const cluster<T, E>& lhs, const cluster<T, E>& rhs) const {
	return lhs.nodes == rhs.nodes;
}

} // namespace zh