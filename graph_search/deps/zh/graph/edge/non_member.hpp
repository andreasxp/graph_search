#pragma once
#include <iostream>
#include "edge_fwd.hpp"

namespace zh {

template <class T, class E> bool operator==(const edge<T, E>& lhs, const edge<T, E>& rhs);
template <class T, class E> bool operator!=(const edge<T, E>& lhs, const edge<T, E>& rhs);
template <class T, class E> bool operator< (const edge<T, E>& lhs, const edge<T, E>& rhs);
template <class T, class E> bool operator> (const edge<T, E>& lhs, const edge<T, E>& rhs);
template <class T, class E> bool operator<=(const edge<T, E>& lhs, const edge<T, E>& rhs);
template <class T, class E> bool operator>=(const edge<T, E>& lhs, const edge<T, E>& rhs);

template <class T, class E> bool operator==(const const_edge<T, E>& lhs, const const_edge<T, E>& rhs);
template <class T, class E> bool operator!=(const const_edge<T, E>& lhs, const const_edge<T, E>& rhs);
template <class T, class E> bool operator< (const const_edge<T, E>& lhs, const const_edge<T, E>& rhs);
template <class T, class E> bool operator> (const const_edge<T, E>& lhs, const const_edge<T, E>& rhs);
template <class T, class E> bool operator<=(const const_edge<T, E>& lhs, const const_edge<T, E>& rhs);
template <class T, class E> bool operator>=(const const_edge<T, E>& lhs, const const_edge<T, E>& rhs);

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const edge<T, E>& e);

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const const_edge<T, E>& e);

} // namespace zh

namespace std {

template<class T, class E>
struct hash<zh::edge<T, E>>;

template<class T, class E>
struct hash<zh::const_edge<T, E>>;

}

#include "non_member.inl"