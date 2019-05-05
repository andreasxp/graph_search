#pragma once
#include <boost/iterator/iterator_adaptor.hpp>
#include "iterator_fwd.hpp"
#include "node_iterator_fwd.hpp"
#include "detail.hpp"

namespace zh {

template <class T, class E>
class graph_iterator
	: public boost::iterator_adaptor<
	graph_iterator<T, E>,
	typename detail::graph_container<T, E>::iterator,
	T,
	boost::iterators::use_default,
	T&> {

private:
	using base_type = boost::iterator_adaptor<
		graph_iterator<T, E>,
		typename detail::graph_container<T, E>::iterator,
		T,
		boost::iterators::use_default,
		T&>;
	friend class boost::iterator_core_access;

	T& dereference() const noexcept;

public:
	using base_type::base_type;
	graph_iterator(graph_node_iterator<T, E> other) noexcept;
};

template <class T, class E>
class graph_const_iterator
	: public boost::iterator_adaptor<
	graph_const_iterator<T, E>,
	typename detail::graph_container<T, E>::const_iterator,
	T,
	boost::iterators::use_default,
	const T&> {

private:
	using base_type = boost::iterator_adaptor<
		graph_const_iterator<T, E>,
		typename detail::graph_container<T, E>::const_iterator,
		T,
		boost::iterators::use_default,
		const T&>;
	friend class boost::iterator_core_access;

	const T& dereference() const noexcept;

public:
	using base_type::base_type;
	graph_const_iterator(graph_iterator<T, E> other) noexcept;
	graph_const_iterator(graph_node_iterator<T, E> other) noexcept;
	graph_const_iterator(graph_const_node_iterator<T, E> other) noexcept;
};

} // namespace zh

#include "iterator.inl"