#pragma once
#include "connection.hpp"
#include "../node/node.hpp"

namespace zh {

template<class T, class E>
connection<T, E>::connection(node<T, E>* node_ptr, manual_ptr<E>&& value_ptr) :
	m_node_ptr(node_ptr),
	m_value_ptr(std::move(value_ptr)) {
}

template<class T, class E>
connection<T, E> connection<T, E>::valueless(const node<T, E>& where) {
	return connection(&const_cast<node<T, E>&>(where), nullptr);
}

template<class T, class E>
connection<T, E> connection<T, E>::blank() {
	return connection(nullptr, nullptr);
}

template<class T, class E>
node<T, E>& connection<T, E>::operator*() const noexcept {
	return *m_node_ptr;
}

template<class T, class E>
node<T, E>* connection<T, E>::get() const noexcept {
	return m_node_ptr;
}

template<class T, class E>
node<T, E>* connection<T, E>::operator->() const noexcept {
	return m_node_ptr;
}

template<class T, class E>
E& connection<T, E>::value() const noexcept {
	return *m_value_ptr;
}

template<class T, class E>
manual_ptr<E>& connection<T, E>::value_ptr() noexcept {
	return m_value_ptr;
}

template<class T, class E>
const manual_ptr<E>& connection<T, E>::value_ptr() const noexcept {
	return m_value_ptr;
}

template<class T, class E>
template<class ...Args>
connection<T, E>::connection(node<T, E>& where, Args&& ...value_args) :
	m_node_ptr(&where),
	m_value_ptr(make_manual<E>(std::forward<Args>(value_args)...)) {
	static_assert(std::is_constructible_v<E, Args&&...>,
		"connection::connection: cannot constuct value_type from these arguments");
}

} // namespace zh