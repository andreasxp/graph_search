#pragma once
#include <boost/iterator/iterator_adaptor.hpp>
#include "detail.hpp"
#include "../edge/edge_fwd.hpp"

namespace zh {

template <class T, class E>
class node_edge_iterator
	: public boost::iterator_adaptor<
	node_edge_iterator<T, E>,
	typename detail::node_container<T, E>::iterator,
	edge<T, E>,
	boost::iterators::use_default,
	edge<T, E>> {

private:
	using base_type = boost::iterator_adaptor<
		node_edge_iterator<T, E>,
		typename detail::node_container<T, E>::iterator,
		edge<T, E>,
		boost::iterators::use_default,
		edge<T, E>>;
	friend class boost::iterator_core_access;

	node<T, E>& m_source;

	edge<T, E> dereference() const noexcept;

public:
	node_edge_iterator(typename detail::node_container<T, E>::iterator iter, node<T, E>& source);
};

template <class T, class E>
class node_const_edge_iterator
	: public boost::iterator_adaptor<
	node_const_edge_iterator<T, E>,
	typename detail::node_container<T, E>::const_iterator,
	const_edge<T, E>,
	boost::iterators::use_default,
	const_edge<T, E>> {

private:
	using base_type = boost::iterator_adaptor<
		node_const_edge_iterator<T, E>,
		typename detail::node_container<T, E>::const_iterator,
		const_edge<T, E>,
		boost::iterators::use_default,
		const_edge<T, E>>;
	friend class boost::iterator_core_access;

	const node<T, E>& m_source;

	const_edge<T, E> dereference() const noexcept;

public:
	node_const_edge_iterator(typename detail::node_container<T, E>::const_iterator iter, const node<T, E>& source);
	node_const_edge_iterator(const node_edge_iterator<T, E>& other);
};

} // namespace zh

#include "edge_iterator.inl"