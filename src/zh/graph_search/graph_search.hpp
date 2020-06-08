#pragma once
#include <set>
#include <zh/graph.hpp>
#include "graph_match.hpp"

namespace zh {

template <class T, class E>
std::set<graph_match> search(const graph<T, E>& source, const graph<T, E>& target);

template <class T, class E>
bool operator==(const graph<T, E>& lhs, const graph<T, E>& rhs);
template <class T, class E>
bool operator!=(const graph<T, E>& lhs, const graph<T, E>& rhs);

}

#include "graph_search.inl"