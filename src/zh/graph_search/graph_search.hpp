#pragma once
#include <set>
#include <zh/graph.hpp>
#include "puff.hpp"

namespace zh {

template <class T, class U, class F = std::equal_to<void>>
std::set<match<T, U>> search(const graph<T>& source, const graph<U>& target, F&& = F());

template <class T>
bool operator==(const graph<T>& lhs, const graph<T>& rhs);
template <class T>
bool operator!=(const graph<T>& lhs, const graph<T>& rhs);

}

#include "graph_search.inl"