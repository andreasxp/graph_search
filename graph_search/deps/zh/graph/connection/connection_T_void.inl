#pragma once
#include "connection_T_void.hpp"

namespace zh {

template<class T>
connection<T, void>::connection(node<T, void>* node_ptr) :
	m_node_ptr(node_ptr) {
}

template<class T>
connection<T, void>::connection(node<T, void>& where) :
	m_node_ptr(&where) {
}

template<class T>
connection<T, void> connection<T, void>::valueless(const node<T, void>& where) {
	return connection(&const_cast<node<T, void>&>(where));
}

template<class T>
connection<T, void> connection<T, void>::blank() {
	return connection(nullptr);
}

template<class T>
node<T, void>& connection<T, void>::operator*() const noexcept {
	return *m_node_ptr;
}

template<class T>
node<T, void>* connection<T, void>::get() const noexcept {
	return m_node_ptr;
}

template<class T>
node<T, void>* connection<T, void>::operator->() const noexcept {
	return m_node_ptr;
}

} // namespace zh