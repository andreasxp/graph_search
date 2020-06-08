#pragma once
#include <cstdint>
#include <zh/graph.hpp>

namespace zh {

template <class T, class E>
void mutate_nodes(graph<T, E>& gr, std::size_t target_size);

template <class T, class E, class ValueGen>
void mutate_nodes(graph<T, E>& gr, std::size_t target_size, ValueGen&& gen);

template <class T, class E>
void mutate_edges(graph<T, E>& gr, double target_ratio);

template <class T, class E, class EdgeGen>
void mutate_edges(graph<T, E>& gr, double target_ratio, EdgeGen&& gen);

} // namespace zh

#include "mutate.inl"