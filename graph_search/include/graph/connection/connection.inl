#pragma once
#include "connection.hpp"
#include "../node/node.hpp"

template<class T, class E>
inline connection<T, E>::connection(node<T>* ptr, const E& value) :
	base(ptr),
	m_value(value) {
}

template<class T, class E>
inline connection<T, E>::connection(node<T>* ptr, E&& value) :
	base(ptr),
	m_value(std::move(value)) {
}

template<class T, class E>
inline connection<T, E>::connection(node<T>* ptr, manual_ptr<E>& value_ptr, bool transfer) :
	base(ptr),
	m_value(value_ptr, transfer) {
}

template<class T, class E>
inline connection<T, E>::connection(node<T>* ptr, const manual_ptr<E>& value_ptr) :
	base(ptr),
	m_value(value_ptr) {
}

template<class T, class E>
inline connection<T, E>::connection(node<T>* ptr, manual_ptr<E>&& value_ptr) :
	base(ptr),
	m_value(std::move(value_ptr)) {
}

template<class T, class E>
inline E& connection<T, E>::value() noexcept {
	return *m_value;
}

template<class T, class E>
inline const E& connection<T, E>::value() const noexcept {
	return *m_value;
}

template<class T>
inline connection<T, void>::connection(node<T>* ptr) :
	m_ptr(ptr) {
}

template<class T>
inline node<T>* connection<T, void>::get() noexcept {
	return m_ptr;
}

template<class T>
inline const node<T>* connection<T, void>::get() const noexcept {
	return m_ptr;
}

template<class T>
inline node<T>* connection<T, void>::operator->() noexcept {
	return get();
}

template<class T>
inline const node<T>* connection<T, void>::operator->() const noexcept {
	return get();
}

template<class T>
inline node<T>& connection<T, void>::operator*() noexcept {
	return *get();
}

template<class T>
inline const node<T>& connection<T, void>::operator*() const noexcept {
	return *get();
}

// Non-member functions =======================================================
template<class T, class E>
inline bool operator==(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	if constexpr (std::is_same_v<E, void>) {
		return lhs.get() == rhs.get();
	}
	else {
		return lhs.get() == rhs.get() && lhs.value() == rhs.value();
	}
}

template<class T, class E>
inline bool operator!=(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	return !(lhs == rhs);
}

template<class T, class E>
inline bool operator< (const connection<T, E>& lhs, const connection<T, E>& rhs) {
	if constexpr (std::is_same_v<E, void>) {
		return lhs.get() < rhs.get();
	}
	else {
		return
			(lhs.get() < rhs.get()) ||
			(lhs.get() == rhs.get() && lhs.value() < rhs.value());
	}
}

template<class T, class E>
inline bool operator> (const connection<T, E>& lhs, const connection<T, E>& rhs) {
	return rhs < lhs;
}

template<class T, class E>
inline bool operator<=(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	return !(lhs > rhs);
}

template<class T, class E>
inline bool operator>=(const connection<T, E>& lhs, const connection<T, E>& rhs) {
	return !(lhs < rhs);
}

namespace std {

template <class T, class E>
struct hash<connection<T, E>> {
	std::size_t operator()(const connection<T, E>& con) const noexcept {
		if constexpr (std::is_same_v<E, void>) {
			return std::hash<const node<T>*>()(con.get());
		}
		else {
			return 
				std::hash<const node<T>*>()(con.get()) xor
				std::hash<E>()(con.value());
		}
	}
};

}