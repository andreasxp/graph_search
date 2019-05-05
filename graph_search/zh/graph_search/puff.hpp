#pragma once
#include <cstdint>
#include <limits> 
#include <set>
#include <vector>

#include "cluster.hpp"
#include "deps/zh/graph.hpp"

namespace zh {

template <class T, class E>
class puff {
public:
	// level_type has sectors of one size
	using level_type = std::vector<cluster<T, E>>;
	// container holds all the levels
	using container_type = std::vector<level_type>;

private:
	container_type sectors;

public:
	// Constructors ===========================================================
	puff() = default;

	puff(const graph<T, E>& gr, std::size_t max_depth = std::numeric_limits<std::size_t>::max());

	puff(const puff& other) = default;
	puff(puff&& other) = default;

	puff& operator=(const puff& other) = default;
	puff& operator=(puff&& other) = default;

	// Observers ==============================================================

	// How many levels this puff has
	std::size_t depth() const noexcept;

	std::size_t count_edges() const noexcept;
	std::size_t count_sectors() const noexcept;
	std::size_t size_in_bytes() const noexcept;

	// Search for another puff in this puff
	std::set<graph_match> search(const puff& other) const;

	const level_type& operator[](std::size_t idx) const;
};

template <class T, class E>
bool operator==(const puff<T, E>& lhs, const puff<T, E>& rhs);

template <class T, class E>
bool operator!=(const puff<T, E>& lhs, const puff<T, E>& rhs);

template <class T, class E>
std::ostream& operator<<(std::ostream& os, const puff<T, E>& obj);

} // namespace zh

#include "puff.inl"