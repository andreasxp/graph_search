#pragma once
#include "connection.hpp"
#include "../node/pseudonode.hpp"

// A wrapper for connection that does not destruct the E in connection after 
// destroyed. Construct this with an id to get a connection with no value and a
// pseudonode equivalent, or construct with an E* to get a connection with a
// particular value but no node to point to. This class is used to lookup
// equivalent real connections in hash sets (Note: written before C++20 and
// K-class overloads in unordered_set).
template <class T, class E = void>
class pseudoconnection {
private:
	// Node to which the imitator will actually point to
	// (if not constructed from a node pointer)
	pseudonode<T> m_pnode;
	connection<T, E> m_imitator;

public:
	operator connection<T, E>&() noexcept;
	operator const connection<T, E>&() const noexcept;

	connection<T, E>& imitator() noexcept;
	const connection<T, E>& imitator() const noexcept;

	pseudoconnection(typename node<T>::id_type id);
	pseudoconnection(node<T>* nd);
	pseudoconnection(E* borrow_value, typename node<T>::id_type id = 0);
	pseudoconnection(E* borrow_value, node<T>* nd);
	~pseudoconnection();
};

template <class T>
class pseudoconnection<T, void> {
private:
	// Node to which the imitator will actually point to
	// (if not constructed from a node pointer)
	pseudonode<T> m_pnode;
	connection<T> m_imitator;

public:
	operator connection<T>&() noexcept;
	operator const connection<T>&() const noexcept;

	connection<T>& imitator() noexcept;
	const connection<T>& imitator() const noexcept;

	pseudoconnection(typename node<T>::id_type id);
	pseudoconnection(node<T>* nd);
};

#include "pseudoconnection.inl"