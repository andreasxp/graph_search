#pragma once
#include <cstdint>
#include <limits> 
#include <set>
#include <vector>
#include <utility>

#include "cluster.hpp"
#include <zh/graph.hpp>

namespace zh {

template <class T>
class puff {
public:
	// level_type has sectors of one size
	using level_type = std::vector<cluster<T>>;
	// container holds all the levels
	using container_type = std::vector<level_type>;	

private:
	container_type sectors;

public:
	// Constructors ===========================================================
	puff() = default;

	puff(const graph<T>& gr, std::size_t max_depth = std::numeric_limits<std::size_t>::max());

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
	template <class U, class F = std::equal_to<void>>
	std::set<match<T, U>> search(const puff<U>& other, F&& compare = F()) const;

	const level_type& operator[](std::size_t idx) const;

	// Friends ================================================================
	template <class T_>
	friend class puff;
};

template <class T>
bool operator==(const puff<T>& lhs, const puff<T>& rhs);

template <class T>
bool operator!=(const puff<T>& lhs, const puff<T>& rhs);

template <class T>
std::ostream& operator<<(std::ostream& os, const puff<T>& obj);

} // namespace zh

#include "puff.inl"