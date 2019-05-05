#pragma once
#include <tuple>
#include "non_member.hpp"
#include "../node/non_member.hpp"
#include "edge.hpp"
#include "const_edge.hpp"

namespace zh {

template <class T, class E> bool operator==(const edge<T, E>& lhs, const edge<T, E>& rhs) { return const_edge<T, E>(lhs) == const_edge<T, E>(rhs); }
template <class T, class E> bool operator!=(const edge<T, E>& lhs, const edge<T, E>& rhs) { return const_edge<T, E>(lhs) != const_edge<T, E>(rhs); }
template <class T, class E> bool operator< (const edge<T, E>& lhs, const edge<T, E>& rhs) { return const_edge<T, E>(lhs) <  const_edge<T, E>(rhs); }
template <class T, class E> bool operator> (const edge<T, E>& lhs, const edge<T, E>& rhs) { return const_edge<T, E>(lhs) >  const_edge<T, E>(rhs); }
template <class T, class E> bool operator<=(const edge<T, E>& lhs, const edge<T, E>& rhs) { return const_edge<T, E>(lhs) <= const_edge<T, E>(rhs); }
template <class T, class E> bool operator>=(const edge<T, E>& lhs, const edge<T, E>& rhs) { return const_edge<T, E>(lhs) >= const_edge<T, E>(rhs); }

template <class T, class E> 
bool operator==(const const_edge<T, E>& lhs, const const_edge<T, E>& rhs) {
	if constexpr (std::is_same_v<E, void>) {
		return
			lhs.first().id() == rhs.first().id() &&
			lhs.second().id() == rhs.second().id();
	}
	else {
		return
			lhs.first().id() == rhs.first().id() &&
			lhs.second().id() == rhs.second().id() &&
			lhs.value() == rhs.value();
	}
}

template <class T, class E> 
bool operator!=(const const_edge<T, E>& lhs, const const_edge<T, E>& rhs) { 
	return !(lhs == rhs); 
}

template <class T, class E> 
bool operator< (const const_edge<T, E>& lhs, const const_edge<T, E>& rhs) {
	if constexpr (std::is_same_v<E, void>) {
		return
			std::tie(lhs.first().id(), lhs.second().id()) <
			std::tie(lhs.first().id(), lhs.second().id());
	}
	else {
		return
			std::tie(lhs.first().id(), lhs.second().id(), lhs.value()) <
			std::tie(lhs.first().id(), lhs.second().id(), rhs.value());
	}
}

template <class T, class E> 
bool operator> (const const_edge<T, E>& lhs, const const_edge<T, E>& rhs) {
	return rhs < lhs;
}

template <class T, class E> 
bool operator<=(const const_edge<T, E>& lhs, const const_edge<T, E>& rhs) {
	return !(rhs < lhs);
}

template <class T, class E> 
bool operator>=(const const_edge<T, E>& lhs, const const_edge<T, E>& rhs) { 
	return !(lhs == rhs); 
}

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const edge<T, E>& e) {
	os << "{#" << e.first().id() << " - #" << e.second().id();

	if constexpr (!std::is_same_v<E, void>) {
		os << " (value: " << e.value() << ")";
	}

	os << "}";

	return os;
}

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const const_edge<T, E>& e) {
	os << "{#" << e.first().id() << " - #" << e.second().id();

	if constexpr (!std::is_same_v<E, void>) {
		os << " (value: " << e.value() << ")";
	}

	os << "}";

	return os;
}

}

namespace std {

template<class T, class E>
struct hash<zh::const_edge<T, E>> {
	std::size_t operator()(const zh::const_edge<T, E>& e) const noexcept {
		std::hash<zh::node<T, E>> node_hash;

		if constexpr (std::is_same_v<E, void>) {
			return
				node_hash(e.first()) xor
				node_hash(e.second());
		}
		else {
			return
				node_hash(e.first()) xor
				node_hash(e.second()) xor
				hash<E>()(e.value());
		}
	}
};

template<class T, class E>
struct hash<zh::edge<T, E>> : private hash<zh::const_edge<T, E>> {
private:
	using base_type = hash<zh::const_edge<T, E>>;

public:
	std::size_t operator()(const zh::edge<T, E>& e) const noexcept {
		return base_type::operator()(e);
	}
};

}