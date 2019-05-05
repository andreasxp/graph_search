#pragma once
#include "edge_fwd.hpp"
#include "../node/node_fwd.hpp"

namespace zh {

template <class T>
class edge<T, void> {
private:
	node<T, void>* m_first_ptr;
	node<T, void>* m_second_ptr;

public:
	// Member types ===========================================================
	using value_type = void;
	using node_type = node<T, void>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	edge(node<T, void>& first, node<T, void>& second);

	edge() = delete;
	edge(const edge&) = default;
	edge(edge&&) = default;

	edge& operator=(const edge&) = default;
	edge& operator=(edge&&) = default;

	// Data access ------------------------------------------------------------
	// Access first node
	node<T, void>& first() noexcept;
	const node<T, void>& first() const noexcept;

	// Access second node
	node<T, void>& second() noexcept;
	const node<T, void>& second() const noexcept;
};

} // namespace zh

#include "non_member.hpp"

#include "edge_T_void.inl"