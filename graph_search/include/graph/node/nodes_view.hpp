#pragma once
#include "node.hpp"
#include "deps/zh/container_view.hpp"

template <class T>
class node<T>::nodes_view : public zh::forward_container_view <
	container,
	node_iterator,
	const_node_iterator> {
private:
	using base = zh::forward_container_view <
		container,
		node_iterator,
		const_node_iterator
	>;

public:
	using base::base;
};

template <class T>
class node<T>::const_nodes_view : public zh::const_forward_container_view<
	container,
	const_node_iterator> {
private:
	using base = zh::const_forward_container_view<
		container,
		const_node_iterator
	>;

public:
	using base::base;
};