#pragma once
#include "non_member.hpp"

namespace zh {

template<class T, class E>
std::ostream& operator<<(std::ostream& os, const node<T, E>& n) {
	os << "{#" << n.id();

	if constexpr (!std::is_same_v<T, void>) {
		os << " (value: " << n.value() << ")";
	}

	os << "}";
	return os;
}

}

namespace std {

template<class T, class E>
struct hash<zh::node<T, E>> {
	hash() = default;

	size_t operator()(zh::node<T, E> const& n) const noexcept {
		return std::hash<const zh::node<T, E>*>()(&n);
	}
};

}