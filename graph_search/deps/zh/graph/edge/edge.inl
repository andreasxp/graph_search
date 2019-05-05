#pragma once
#include <cassert>
#include "edge.hpp"

namespace zh {

template<class T, class E>
edge<T, E>::edge(node<T, E>& first, node<T, E>& second, E& value) :
	m_first_ptr(&first),
	m_second_ptr(&second),
	m_value_ptr(&value) {
}

template<class T, class E>
node<T, E>& edge<T, E>::first() noexcept {
	return *m_first_ptr;
}

template<class T, class E>
const node<T, E>& edge<T, E>::first() const noexcept {
	return *m_first_ptr;
}

template<class T, class E>
node<T, E>& edge<T, E>::second() noexcept {
	return *m_second_ptr;
}

template<class T, class E>
const node<T, E>& edge<T, E>::second() const noexcept {
	return *m_second_ptr;
}

template<class T, class E>
E& edge<T, E>::value() noexcept {
	return *m_value_ptr;
}

template<class T, class E>
const E& edge<T, E>::value() const noexcept {
	return *m_value_ptr;
}

} // namespace zh