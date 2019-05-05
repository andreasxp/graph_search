#pragma once
#include <range/v3/all.hpp>
#include "detail.hpp"
#include "graph.hpp"

namespace zh {

template <class T, class E>
class graph_edges_view : public detail::graph_edges_view_raw<T, E> {
private:
	using base_type = detail::graph_edges_view_raw<T, E>;

	detail::graph_container<T, E>& m_data;

public:
	// Member types ===========================================================
	using value_type      = edge<T, E>;

	using size_type       = std::size_t;
	using difference_type = std::ptrdiff_t;

	using iterator        = decltype(std::declval<base_type>().begin());

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	graph_edges_view(detail::graph_container<T, E>& c);

	// Operations -------------------------------------------------------------
	std::size_t size() const noexcept;
	bool empty() const noexcept;

	// Friends ================================================================
	template <class T_, class E_>
	friend class graph_const_edges_view;
};

template <class T, class E>
class graph_const_edges_view : public detail::graph_const_edges_view_raw<T, E> {
private:
	using base_type = detail::graph_const_edges_view_raw<T, E>;

	const detail::graph_container<T, E>& m_data;

public:
	// Member types ===========================================================
	using value_type      = const_edge<T, E>;

	using size_type       = std::size_t;
	using difference_type = std::ptrdiff_t;

	using iterator        = decltype(std::declval<base_type>().begin());

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	graph_const_edges_view(const detail::graph_container<T, E>& c);
	graph_const_edges_view(const graph_edges_view<T, E>& view);

	// Operations -------------------------------------------------------------
	std::size_t size() const noexcept;
	bool empty() const noexcept;
};

} // namespace zh

#include "edges_view.inl"