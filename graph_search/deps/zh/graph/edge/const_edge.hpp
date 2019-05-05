#pragma once
#include "edge_fwd.hpp"
#include "../node/node_fwd.hpp"

namespace zh {

template <class T, class E>
class const_edge {
private:
	const node<T, E>* m_first_ptr;
	const node<T, E>* m_second_ptr;
	const E* m_value_ptr;

public:
	// Member types ===========================================================
	using value_type = E;
	using node_type = node<T, E>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	const_edge(const node<T, E>& first, const node<T, E>& second, const E& value);

	const_edge(const edge<T, E>& other) noexcept;

	const_edge() = delete;
	const_edge(const const_edge&) = default;
	const_edge(const_edge&&) = default;

	const_edge& operator=(const const_edge&) = default;
	const_edge& operator=(const_edge&&) = default;

	// Data access ------------------------------------------------------------
	// Access first node
	const node<T, E>& first() const noexcept;

	// Access second node
	const node<T, E>& second() const noexcept;

	// Access edge value
	const E& value() const noexcept;
};

} // namespace zh

#include "const_edge_T_void.hpp"

#include "non_member.hpp"

#include "const_edge.inl"