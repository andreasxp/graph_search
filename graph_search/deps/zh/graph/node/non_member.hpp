#pragma once
#include <iostream>
#include "node_fwd.hpp"

namespace zh {

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const node<T, E>& n);

}

namespace std {

template<class T, class E>
struct hash<zh::node<T, E>>;

}

#include "non_member.inl"