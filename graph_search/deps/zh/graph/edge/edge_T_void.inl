#pragma once
#include "edge_T_void.hpp"

namespace zh {

template<class T>
edge<T, void>::edge(node<T, void>& first, node<T, void>& second) :
	m_first_ptr(&first),
	m_second_ptr(&second) {
}

template<class T>
node<T, void>& edge<T, void>::first() noexcept {
	return *m_first_ptr;
}

template<class T>
const node<T, void>& edge<T, void>::first() const noexcept {
	return *m_first_ptr;
}

template<class T>
node<T, void>& edge<T, void>::second() noexcept {
	return *m_second_ptr;
}

template<class T>
const node<T, void>& edge<T, void>::second() const noexcept {
	return *m_second_ptr;
}

} // namespace zh