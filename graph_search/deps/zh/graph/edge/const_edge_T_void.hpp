#pragma once
#include "edge_fwd.hpp"
#include "../node/node_fwd.hpp"

namespace zh {

template <class T>
class const_edge<T, void> {
private:
	const node<T, void>* m_first_ptr;
	const node<T, void>* m_second_ptr;

public:
	// Member types ===========================================================
	using value_type = void;
	using node_type = node<T, void>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	const_edge(const node<T, void>& first, const node<T, void>& second);

	const_edge(const edge<T, void>& other) noexcept;

	const_edge() = delete;
	const_edge(const const_edge&) = default;
	const_edge(const_edge&&) = default;

	const_edge& operator=(const const_edge&) = default;
	const_edge& operator=(const_edge&&) = default;

	// Data access ------------------------------------------------------------
	// Access first node
	const node<T, void>& first() const noexcept;

	// Access second node
	const node<T, void>& second() const noexcept;
};

} // namespace zh

#include "non_member.hpp"

#include "const_edge_T_void.inl"