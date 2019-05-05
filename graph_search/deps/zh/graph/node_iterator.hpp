#pragma once
#include <boost/iterator/indirect_iterator.hpp>
#include "node_iterator_fwd.hpp"
#include "iterator_fwd.hpp"
#include "detail.hpp"

namespace zh {

template <class T, class E>
class graph_node_iterator
	: public boost::indirect_iterator<typename detail::graph_container<T, E>::iterator> {
private:
	using base_type = boost::indirect_iterator<typename detail::graph_container<T, E>::iterator>;

public:
	using base_type::base_type;
	graph_node_iterator(graph_iterator<T, E> other) noexcept;
};

template <class T, class E>
class graph_const_node_iterator
	: public boost::indirect_iterator<
		typename detail::graph_container<T, E>::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<T, E>&> {
private:
	using base_type = boost::indirect_iterator<
		typename detail::graph_container<T, E>::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<T, E>&>;

public:
	using base_type::base_type;
	graph_const_node_iterator(graph_node_iterator<T, E> other) noexcept;
	graph_const_node_iterator(graph_iterator<T, E> other) noexcept;
	graph_const_node_iterator(graph_const_iterator<T, E> other) noexcept;
};

} // namespace zh

#include "node_iterator_void_E.hpp"

#include "node_iterator.inl"