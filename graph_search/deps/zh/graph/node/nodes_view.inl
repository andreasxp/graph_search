#pragma once
#include "nodes_view.hpp"

namespace zh {

// node_nodes_view ============================================================
template<class T, class E>
typename node_nodes_view<T, E>::iterator
node_nodes_view<T, E>::find(const node<T, E>& nd) {
	return this->base().find(connection<T, E>::valueless(nd));
}

template<class T, class E>
typename node_nodes_view<T, E>::const_iterator
node_nodes_view<T, E>::find(const node<T, E>& nd) const {
	return this->base().find(connection<T, E>::valueless(nd));
}

template<class T, class E>
bool node_nodes_view<T, E>::contains(const node<T, E>& nd) const {
	return find(nd) != this->end();
}

// node_const_nodes_view ======================================================
template <class T, class E>
node_const_nodes_view<T, E>::node_const_nodes_view(const node_nodes_view<T, E>& other) :
	base_type(static_cast<typename node_nodes_view<T, E>::base const&>(other)) {
}

template<class T, class E>
typename node_const_nodes_view<T, E>::const_iterator
node_const_nodes_view<T, E>::find(const node<T, E>& nd) const {
	return this->base().find(connection<T, E>::valueless(nd));
}

template<class T, class E>
bool node_const_nodes_view<T, E>::contains(const node<T, E>& nd) const {
	return find(nd) != this->end();
}

} // namespace zh