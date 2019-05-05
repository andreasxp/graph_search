#pragma once
#include "const_edge_T_void.hpp"
#include "edge_T_void.hpp"

namespace zh {

template<class T>
const_edge<T, void>::const_edge(const node<T, void>& first, const node<T, void>& second) :
	m_first_ptr(&first),
	m_second_ptr(&second) {
}

template<class T>
const_edge<T, void>::const_edge(const edge<T, void>& other) noexcept :
	m_first_ptr(&other.first()),
	m_second_ptr(&other.second()) {
}

template<class T>
const node<T, void>& const_edge<T, void>::first() const noexcept {
	return *m_first_ptr;
}

template<class T>
const node<T, void>& const_edge<T, void>::second() const noexcept {
	return *m_second_ptr;
}

} // namespace zh