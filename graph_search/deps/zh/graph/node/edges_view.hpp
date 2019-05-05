#pragma once
#include <tuple>
#include "deps/zh/prism.hpp"
#include "node_fwd.hpp"
#include "edge_iterator.hpp"

namespace zh {

template <class T, class E>
class node_edges_view
	: public zh::fprism<
	detail::node_container<T, E>,
	node_edge_iterator<T, E>,
	node_const_edge_iterator<T, E>,
	std::tuple<node<T, E>&>> {
private:
	using base_type = zh::fprism<
		detail::node_container<T, E>,
		node_edge_iterator<T, E>,
		node_const_edge_iterator<T, E>,
		std::tuple<node<T, E>&>>;

	template <class T_, class E_>
	friend class node_const_edges_view;
public:
	node_edges_view(detail::node_container<T, E>& data, node<T, E>& value) :
		base_type(data, std::tie(value)) {
	}
};

template <class T, class E>
class node_const_edges_view
	: public zh::cfprism<
	const detail::node_container<T, E>,
	node_const_edge_iterator<T, E>,
	std::tuple<const node<T, E>&>> {
private:
	using base_type = zh::cfprism<
		const detail::node_container<T, E>,
		node_const_edge_iterator<T, E>,
		std::tuple<const node<T, E>&>>;

public:
	node_const_edges_view(const detail::node_container<T, E>& data, const node<T, E>& value) :
		base_type(data, std::tie(value)) {
	}
	
	node_const_edges_view(const node_edges_view<T, E>& other) :
		base_type(other.m_data) {
	}
};

} // namespace zh