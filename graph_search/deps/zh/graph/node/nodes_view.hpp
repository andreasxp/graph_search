#pragma once
#include "deps/zh/prism.hpp"
#include "node_iterator.hpp"
#include "node_fwd.hpp"
#include "detail.hpp"

namespace zh {

template <class T, class E>
class node_nodes_view
	: public zh::fprism<
		detail::node_container<T, E>,
		node_node_iterator<T, E>,
		node_const_node_iterator<T, E>> {
private:
	using base_type = zh::fprism<
		detail::node_container<T, E>,
		node_node_iterator<T, E>,
		node_const_node_iterator<T, E>>;

	template <class T_, class E_>
	friend class node_const_nodes_view;
public:
	using base_type::base_type;

	using iterator       = typename base_type::iterator;
	using const_iterator = typename base_type::const_iterator;
	// other typedefs are not explicitly defined because not needed in class definition.
	// they are still available for class users.

	iterator       find(const node<T, E>& nd);
	const_iterator find(const node<T, E>& nd) const;

	bool contains(const node<T, E>& nd) const;
};

template <class T, class E>
class node_const_nodes_view
	: public zh::cfprism<
		const detail::node_container<T, E>,
		node_const_node_iterator<T, E>> {
private:
	using base_type = zh::cfprism<
		const detail::node_container<T, E>,
		node_const_node_iterator<T, E>>;

public:
	using const_iterator = typename base_type::const_iterator;
	// other typedefs are not explicitly defined because not needed in class definition.
	// they are still available for class users.

	using base_type::base_type;
	node_const_nodes_view(const node_nodes_view<T, E>& other);

	typename base_type::const_iterator find(const node<T, E>& nd) const;

	bool contains(const node<T, E>& nd) const;
};

} // namespace zh

#include "nodes_view.inl"