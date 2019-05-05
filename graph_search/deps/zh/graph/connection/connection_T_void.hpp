#pragma once
#include "connection_fwd.hpp"

namespace zh {

template <class T>
class connection<T, void> {
private:
	node<T, void>* m_node_ptr;

	explicit connection(node<T, void>* node_ptr);

public:
	// Member types ===========================================================
	using value_type = void;
	using element_type = node<T, void>;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	connection() = delete;

	connection(const connection&) = delete;
	connection(connection&&) = default;

	connection& operator=(const connection&) = delete;
	connection& operator=(connection&&) = default;

	explicit connection(node<T, void>& where);

	template <class T_, class E_, class... Args>
	friend std::pair<connection<T_, E_>, connection<T_, E_>>
		make_connections(node<T_, E_>& first, node<T_, E_>& second, Args&& ... value_args);

	// Fake connection constructors
	// These don't construct actual valid connections. They accept const
	// references and cast const away.
	// These are intended to be used for searching purpuses. Use with caution.
	//static connection unpointed();
	static connection valueless(const node<T, void>& where);
	static connection blank();

	// Member access ----------------------------------------------------------
	node<T, void>& operator*() const noexcept;
	node<T, void>* get() const noexcept;
	node<T, void>* operator->() const noexcept;
};

} // namespace zh

#include "non_member.hpp"

#include "connection_T_void.inl"