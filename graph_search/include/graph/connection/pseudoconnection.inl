#pragma once
#include "pseudoconnection.hpp"

template<class T, class E>
inline pseudoconnection<T, E>::operator connection<T, E>&() noexcept {
	return m_imitator;
}

template<class T, class E>
inline pseudoconnection<T, E>::operator const connection<T, E>&() const noexcept {
	return m_imitator;
}

template<class T, class E>
inline connection<T, E>& pseudoconnection<T, E>::imitator() noexcept {
	return m_imitator;
}

template<class T, class E>
inline const connection<T, E>& pseudoconnection<T, E>::imitator() const noexcept {
	return m_imitator;
}

template<class T, class E>
inline pseudoconnection<T, E>::pseudoconnection(typename node<T>::id_type id) :
	m_pnode(id),
	m_imitator(&m_pnode.imitator()) {
}

template<class T, class E>
inline pseudoconnection<T, E>::pseudoconnection(node<T>* nd) :
	m_pnode(0),
	m_imitator(nd) {
}

template<class T, class E>
inline pseudoconnection<T, E>::pseudoconnection(E* borrow_value, typename node<T>::id_type id) :
	m_pnode(id),
	m_imitator(borrow_value, &m_pnode.imitator()) {
}

template<class T, class E>
inline pseudoconnection<T, E>::pseudoconnection(E* borrow_value, node<T>* nd) :
	m_pnode(0),
	m_imitator(borrow_value, nd) {
}

template<class T, class E>
inline pseudoconnection<T, E>::~pseudoconnection() {
	// Since pseudoconnection was constructed with a borrowed value,
	// that value is not destructed and the deleter is released.
	m_imitator.m_value.release();
}

template<class T>
inline pseudoconnection<T, void>::operator connection<T>&() noexcept {
	return m_imitator;
}

template<class T>
inline pseudoconnection<T, void>::operator const connection<T>&() const noexcept {
	return m_imitator;
}

template<class T>
inline connection<T>& pseudoconnection<T, void>::imitator() noexcept {
	return m_imitator;
}

template<class T>
inline const connection<T>& pseudoconnection<T, void>::imitator() const noexcept {
	return m_imitator;
}

template<class T>
inline pseudoconnection<T, void>::pseudoconnection(typename node<T>::id_type id) :
	m_pnode(id),
	m_imitator(&m_pnode.imitator()) {
}

template<class T>
inline pseudoconnection<T, void>::pseudoconnection(node<T>* nd) :
	m_pnode(0),
	m_imitator(nd) {
}