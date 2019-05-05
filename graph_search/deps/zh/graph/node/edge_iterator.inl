#pragma once
#include "edge_iterator.hpp"

namespace zh {

template <class T, class E>
node_edge_iterator<T, E>::node_edge_iterator(typename detail::node_container<T, E>::iterator iter, node<T, E>& source) :
	base_type(iter),
	m_source(source) {
}

template <class T, class E>
edge<T, E> node_edge_iterator<T, E>::dereference() const noexcept {
	if constexpr (std::is_same_v<E, void>) {
		return edge<T, E>(m_source, *this->base_reference()); // no value
	}
	else {
		return edge<T, E>(m_source, *this->base_reference(), this->base_reference()->value());
	}
}

template <class T, class E>
node_const_edge_iterator<T, E>::node_const_edge_iterator(typename detail::node_container<T, E>::const_iterator iter, const node<T, E>& source) :
	base_type(iter),
	m_source(source) {
}

template <class T, class E>
const_edge<T, E> node_const_edge_iterator<T, E>::dereference() const noexcept {
	const node<T, E>& target = **this->base_reference();

	if constexpr (std::is_same_v<E, void>) {
		// no edge value

		if (m_source.id() < target.id())
			return const_edge<T, E>(m_source, target);
		else 
			return const_edge<T, E>(target, m_source);
	}
	else {
		if (m_source.id() < target.id())
			return const_edge<T, E>(m_source, target, this->base_reference()->value());
		else
			return const_edge<T, E>(target, m_source, this->base_reference()->value());
	}
}

template <class T, class E>
node_const_edge_iterator<T, E>::node_const_edge_iterator(const node_edge_iterator<T, E>& other) :
	node_const_edge_iterator(other.base(), other.m_source) {
}

} // namespace zh