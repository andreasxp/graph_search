#pragma once
#include <boost/iterator/indirect_iterator.hpp>
#include "node_fwd.hpp"
#include "detail.hpp"

namespace zh {

template <class T, class E>
class node_node_iterator
	: public boost::indirect_iterator<typename detail::node_container<T, E>::iterator> {
private:
	using base_type = boost::indirect_iterator<typename detail::node_container<T, E>::iterator>;

public:
	using base_type::base_type;
};

template <class T, class E>
class node_const_node_iterator
	: public boost::indirect_iterator<
		typename detail::node_container<T, E>::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<T, E>&> {
private:
	using base_type = boost::indirect_iterator<
		typename detail::node_container<T, E>::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<T, E>&>;

public:
	using base_type::base_type;
	node_const_node_iterator(node_node_iterator<T, E> other) :
		base_type(other.base()) {}
};

} // namespace zh