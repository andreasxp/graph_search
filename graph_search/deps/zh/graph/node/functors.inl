#pragma once
#include "functors.hpp"
#include "node.hpp"

namespace zh {

template<class T, class E>
bool node_id_equal::operator()(const node<T, E>& lhs, const node<T, E>& rhs) const noexcept {
	return lhs.id() == rhs.id();
}

} // namespace zh