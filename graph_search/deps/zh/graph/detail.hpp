#pragma once
#include <vector>
#include <memory>
#include "node/node_fwd.hpp"
#include "edge/edge.hpp"

namespace zh {
namespace detail {

template <class T, class E>
using graph_container = std::vector<std::unique_ptr<node<T, E>>>;

template <class T, class E>
auto make_edges_view(graph_container<T, E>& c) {
	return ranges::view::for_each(c, [] (auto & node_ptr) {
		auto& nd1 = *node_ptr;
		
		return ranges::view::for_each(nd1.m_connections, [&nd1] (auto & con) {
			auto& nd2 = *con;
			
			if constexpr (std::is_same_v<E, void>) {
				return ranges::yield_if(nd1.id() < nd2.id(), edge<T, void>(nd1, nd2));
			}
			else {
				return ranges::yield_if(nd1.id() < nd2.id(), edge<T, E>(nd1, nd2, con.value()));
			}
		});
	});
}

template <class T, class E>
auto make_edges_view(const graph_container<T, E>& c) {
	return ranges::view::for_each(c, [] (auto & node_ptr) {
		auto& nd1 = *node_ptr;
		
		return ranges::view::for_each(nd1.m_connections, [&nd1] (auto & con) {
			auto& nd2 = *con;
			
			if constexpr (std::is_same_v<E, void>) {
				return ranges::yield_if(nd1.id() < nd2.id(), const_edge<T, void>(nd1, nd2));
			}
			else {
				return ranges::yield_if(nd1.id() < nd2.id(), const_edge<T, E>(nd1, nd2, con.value()));
			}
		});
	});
}

template <class T, class E>
using graph_edges_view_raw
	= decltype(make_edges_view(std::declval<graph_container<T, E>&>()));
template <class T, class E>
using graph_const_edges_view_raw
	= decltype(make_edges_view(std::declval<const graph_container<T, E>&>()));

} // namespace detail
} // namespace zh