#pragma once
#include <iostream>
#include "graph_fwd.hpp"

namespace zh {

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const graph<T, E>& obj);

template<class T, class E>
void swap(graph<T, E>& lhs, graph<T, E>& rhs) noexcept;

} // namespace zh

#include "non_member.inl"