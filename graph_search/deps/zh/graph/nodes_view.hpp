#pragma once
#include "deps/zh/prism.hpp"
#include "detail.hpp"
#include "node_iterator.hpp"

namespace zh {

template <class T, class E>
class graph_nodes_view
	: public zh::fprism<
		detail::graph_container<T, E>,
		graph_node_iterator<T, E>,
		graph_const_node_iterator<T, E>> {
private:
	using base_type = zh::fprism<
		detail::graph_container<T, E>,
		graph_node_iterator<T, E>,
		graph_const_node_iterator<T, E>>;

public:
	using base_type::base_type;

	template <class T_, class E_>
	friend class graph_const_nodes_view;
};

template <class T, class E>
class graph_const_nodes_view
	: public zh::cfprism<
		const detail::graph_container<T, E>,
		graph_const_node_iterator<T, E>> {
private:
	using base_type = zh::cfprism<
		const detail::graph_container<T, E>,
		graph_const_node_iterator<T, E>>;

public:
	using base_type::base_type;
	graph_const_nodes_view(const graph_nodes_view<T, E>& other) :
		base_type(other.m_data) {
	}
};

} // namespace zh