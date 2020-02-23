#pragma once
#include <utility>
#include "connection_fwd.hpp"
#include "../node/node_fwd.hpp"

namespace zh {

template<class T, class E> inline bool operator==(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator!=(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator< (const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator> (const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator<=(const connection<T, E>& lhs, const connection<T, E>& rhs);
template<class T, class E> inline bool operator>=(const connection<T, E>& lhs, const connection<T, E>& rhs);

// Make two connections, from first to second and in reverse, with one value.
template <class T, class E, class... Args>
std::pair<connection<T, E>, connection<T, E>>
make_connections(node<T, E>& first, node<T, E>& second, Args&&... value_args);

} // namespace zh

namespace std {

template <class T, class E>
struct hash<zh::connection<T, E>>;

}

#include "non_member.inl"