#pragma once
#include "edge_fwd.hpp"
#include "../node/node_fwd.hpp"

namespace zh {

// Although called edge, this is more like an edge-reference.
// Due to implementation details, graph does not hold actual edges as objects,
// only nodes and connections. This is an interface for the user to interact
// with the graph in the edges paradigm.
//
// An edge does not care if the graph is oriented or not. If the graph is
// oriented, it constructs edges in such a way that first() always returns
// the source node, and second() - the target node.
template <class T, class E>
class edge {
private:
	node<T, E>* m_first_ptr;
	node<T, E>* m_second_ptr;
	E*          m_value_ptr;

public:
	// Member types ===========================================================
	using value_type = E;
	using node_type = node<T, E>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	edge(node<T, E>& first, node<T, E>& second, E& value);

	edge()                       = delete;
	edge(const edge&)            = default;
	edge(edge&&)                 = default;

	edge& operator=(const edge&) = default;
	edge& operator=(edge&&)      = default;

	// Data access ------------------------------------------------------------
	// Access first node
	node<T, E>& first() noexcept;
	const node<T, E>& first() const noexcept;

	// Access second node
	node<T, E>& second() noexcept;
	const node<T, E>& second() const noexcept;

	// Access edge value
	E& value() noexcept;
	const E& value() const noexcept;
};

} // namespace zh

#include "edge_T_void.hpp"
#include "const_edge.hpp"

#include "non_member.hpp"

#include "edge.inl"