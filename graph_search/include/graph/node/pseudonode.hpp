#pragma once
#include "node.hpp"

// A wrapper for node that does not destruct the T in node after destroyed.
// Construct this with an id to get a node with a particular id for lookup
// in hash sets. (Note: written before C++20 and K-class overloads in 
// unordered_set).
template <class T>
class pseudonode {
private:
	node<T> m_imitator;

public:
	operator node<T>&() noexcept;
	operator const node<T>&() const noexcept;
	
	node<T>& imitator() noexcept;
	const node<T>& imitator() const noexcept;

	pseudonode(typename node<T>::id_type id);
	~pseudonode();
};

#include "pseudonode.inl"
