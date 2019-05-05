#pragma once
#include <boost/iterator/indirect_iterator.hpp>
#include "detail.hpp"
#include "node_iterator.hpp"

namespace zh {

template <class E>
class graph_node_iterator<void, E>
	: public boost::indirect_iterator<typename detail::graph_container<void, E>::iterator> {
private:
	using base_type = boost::indirect_iterator<typename detail::graph_container<void, E>::iterator>;

public:
	using base_type::base_type;

	template <class T_, class E_>
	class graph_const_node_iterator;
};

template <class E>
class graph_const_node_iterator<void, E>
	: public boost::indirect_iterator<
	typename detail::graph_container<void, E>::const_iterator,
	boost::iterators::use_default,
	boost::iterators::use_default,
	const node<void, E>&> {
private:
	using base_type = boost::indirect_iterator<
		typename detail::graph_container<void, E>::const_iterator,
		boost::iterators::use_default,
		boost::iterators::use_default,
		const node<void, E>&>;

public:
	using base_type::base_type;
	graph_const_node_iterator(graph_node_iterator<void, E> other) noexcept;
};

} // namespace zh

#include "node_iterator_void_E.inl"