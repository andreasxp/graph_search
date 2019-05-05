#pragma once
#include "deps/nlohmann/json.hpp"
#include "deps/zh/graph.hpp"
using json = nlohmann::json;

namespace zh {

template <class T, class E>
void from_json(const json& j, graph<T, E>& gr);

template <class T, class E>
void to_json(json& j, const graph<T, E>& gr);

} // namespace zh

#include "json.inl"