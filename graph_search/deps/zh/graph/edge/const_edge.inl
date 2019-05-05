#pragma once
#include "const_edge.hpp"
#include "edge.hpp"

namespace zh {

template<class T, class E>
const_edge<T, E>::const_edge(const node<T, E>& first, const node<T, E>& second, const E& value) :
	m_first_ptr(&first),
	m_second_ptr(&second),
	m_value_ptr(&value) {
}

template<class T, class E>
const_edge<T, E>::const_edge(const edge<T, E>& other) noexcept :
	m_first_ptr(&other.first()),
	m_second_ptr(&other.second()),
	m_value_ptr(&other.value()) {
}

template<class T, class E>
const node<T, E>& const_edge<T, E>::first() const noexcept {
	return *m_first_ptr;
}

template<class T, class E>
const node<T, E>& const_edge<T, E>::second() const noexcept {
	return *m_second_ptr;
}

template<class T, class E>
const E& const_edge<T, E>::value() const noexcept {
	return *m_value_ptr;
}

} // namespace zh