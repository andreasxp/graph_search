#pragma once
#include "node_fwd.hpp"

namespace zh {

// Equality operator that returns true if node IDs are the same
struct node_id_equal {
	template<class T, class E>
	bool operator() (const node<T, E>& lhs, const node<T, E>& rhs) const noexcept;
};

} // namespace zh

#include "functors.inl"