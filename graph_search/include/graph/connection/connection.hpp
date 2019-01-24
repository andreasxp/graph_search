#pragma once
#include "deps/manual_ptr.hpp"

template <class T>
class node;

// Connection represents a "connection" one node has to another.
// This is not an edge, because an edge holds information about both source
// and target nodes, while a connection is closer to a "pointer with data".
// Connection is sometimes responsible for deleting E (value) (see 
// manual_ptr.hpp), and never responsible for deleting nodes it's pointing to.
template <class T, class E = void>
class connection : public connection<T, void> {
private:
	using base = connection<T, void>;

	manual_ptr<E> m_value;

public:
	connection(node<T>* ptr, const E& value);
	connection(node<T>* ptr, E&& value);
	connection(node<T>* ptr, manual_ptr<E>& value_ptr, bool transfer);
	connection(node<T>* ptr, const manual_ptr<E>& value_ptr);
	connection(node<T>* ptr, manual_ptr<E>&& value_ptr);

	// m_ptr and public accessors are derived from connection<T, void>
	E& value() noexcept;
	const E& value() const noexcept;

	template <class T, class E>
	friend class pseudoconnection;
};

template <class T>
class connection<T, void> {
private:
	node<T>* m_ptr;

public:
	connection(node<T>* ptr);

	node<T>* get() noexcept;
	const node<T>* get() const noexcept;

	node<T>* operator->() noexcept;
	const node<T>* operator->() const noexcept;

	node<T>& operator*() noexcept;
	const node<T>& operator*() const noexcept;
};

template<class T, class E> inline bool operator==(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator!=(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator< (const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator> (const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator<=(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator>=(const connection<T, E>& lhs, const connection<T, E>& rhs);

namespace std {

template <class T, class E>
struct hash<connection<T, E>>;

}

#include "connection.inl"