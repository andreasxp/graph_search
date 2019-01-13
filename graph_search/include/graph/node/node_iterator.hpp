#pragma once
#include "node.hpp"

#include <iterator>
#include "deps/zh/proxy_iterator.hpp"

template <class T>
class node<T>::node_iterator
	: public zh::proxy_iterator<container_iterator, zh::proxy::dereference> {
	using base = zh::proxy_iterator<container_iterator, zh::proxy::dereference>;
public:
	// Member types =======================================================
	using value_type
		= typename std::iterator_traits<base>::value_type;
	using difference_type
		= typename std::iterator_traits<base>::difference_type;
	using pointer
		= typename std::iterator_traits<base>::pointer;
	using reference
		= typename std::iterator_traits<base>::reference;
	using iterator_category
		= typename std::iterator_traits<base>::iterator_category;

	// Constructors =======================================================

	// From internal container
	node_iterator(const container_iterator& other);
};

template <class T>
class node<T>::const_node_iterator : public zh::proxy_iterator<
	const_container_iterator, zh::proxy::dereference, zh::proxy::add_const> {
	using base = zh::proxy_iterator<
		const_container_iterator, zh::proxy::dereference, zh::proxy::add_const>;
public:
	// Member types =======================================================
	using value_type
		= typename std::iterator_traits<base>::value_type;
	using difference_type
		= typename std::iterator_traits<base>::difference_type;
	using pointer
		= typename std::iterator_traits<base>::pointer;
	using reference
		= typename std::iterator_traits<base>::reference;
	using iterator_category
		= typename std::iterator_traits<base>::iterator_category;

	// Constructors =======================================================

	// Default
	const_node_iterator() = default;

	// Make const
	const_node_iterator(const node_iterator& other);

	// From internal container
	const_node_iterator(const const_container_iterator& other);
};

#include "node_iterator.inl"