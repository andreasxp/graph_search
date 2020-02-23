#pragma once
#include "edges_view.hpp"

namespace zh {

// graph_edges_view ===========================================================
template<class T, class E>
inline graph_edges_view<T, E>::graph_edges_view(detail::graph_container<T, E>& c) :
	base_type(detail::make_edges_view(c)),
	m_data(c) {
}

template<class T, class E>
inline std::size_t graph_edges_view<T, E>::size() const noexcept {
	std::size_t result = 0;

	for (auto&& node_ptr : m_data) {
		result += node_ptr->adjacent_nodes().size();
	}

	return result / 2;
}

template<class T, class E>
inline bool graph_edges_view<T, E>::empty() const noexcept {
	return size() == 0;
}

// graph_const_edges_view =====================================================
template<class T, class E>
inline graph_const_edges_view<T, E>::graph_const_edges_view(const detail::graph_container<T, E>& c) :
	base_type(detail::make_edges_view(c)),
	m_data(c) {
}

template<class T, class E>
inline graph_const_edges_view<T, E>::graph_const_edges_view(const graph_edges_view<T, E>& view) :
	base_type(detail::make_edges_view(view.m_data)),
	m_data(view.m_data) {
}

template<class T, class E>
inline std::size_t graph_const_edges_view<T, E>::size() const noexcept {
	std::size_t result = 0;

	for (auto&& node_ptr : m_data) {
		result += node_ptr->adjacent_nodes().size();
	}

	return result / 2;
}

template<class T, class E>
inline bool graph_const_edges_view<T, E>::empty() const noexcept {
	return size() == 0;
}

} // namespace zh