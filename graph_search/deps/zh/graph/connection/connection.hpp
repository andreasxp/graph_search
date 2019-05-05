#pragma once
#include <variant>
#include "connection_fwd.hpp"
#include "deps/zh/manual_ptr.hpp"
#include "../node/node_fwd.hpp"

namespace zh {

// Connection represents a "connection" one node has to another.
// This is not an edge, because an edge holds information about both source
// and target nodes, while a connection is a "pointer with extra data".
// Connection is sometimes responsible for deleting E (value) (see 
// manual_ptr.hpp), and never responsible for deleting nodes it's pointing to.
template <class T, class E>
class connection {
private:
	node<T, E>*   m_node_ptr;
	manual_ptr<E> m_value_ptr;

	connection(node<T, E>* node_ptr, manual_ptr<E>&& value_ptr);

public:
	// Member types ===========================================================
	using value_type = E;
	using element_type = node<T, E>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	connection() = delete;

	connection(const connection&) = delete;
	connection(connection&&) = default;

	connection& operator=(const connection&) = delete;
	connection& operator=(connection&&) = default;

	template <class... Args>
	explicit connection(node<T, E>& where, Args&&... value_args);

	template <class T_, class E_, class... Args>
	friend std::pair<connection<T_, E_>, connection<T_, E_>>
	make_connections(node<T_, E_>& first, node<T_, E_>& second, Args&&... value_args);

	// Fake connection constructors
	// These don't construct actual valid connections. They accept const
	// references and cast const away.
	// These are intended to be used for searching purpuses. Use with caution.
	//template <class... Args>
	//static connection unpointed(Args&&... value_args);
	static connection valueless(const node<T, E>& where);
	static connection blank();

	// Member access ----------------------------------------------------------
	node<T, E>& operator*() const noexcept;
	node<T, E>* get() const noexcept;
	node<T, E>* operator->() const noexcept;

	E& value() const noexcept;
	manual_ptr<E>& value_ptr() noexcept;
	const manual_ptr<E>& value_ptr() const noexcept;
};

} // namespace zh

#include "connection_T_void.hpp"
#include "non_member.hpp"
#include "functors.hpp"

#include "connection.inl"