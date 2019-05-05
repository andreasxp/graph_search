#pragma once
#include "level_builder.hpp"

#include "deps/ska/bytell_hash_map.hpp"
#include "deps/zh/type_traits.hpp"
#include "deps/ctpl_stl.h"

#include "../node_group.hpp"
#include "safe_sectors_view.hpp"
#include "build_result.hpp"

namespace zh {

template <class T, class E>
class level_builder<T, E, true> {
private:
	using sources_t = ska::bytell_hash_map<node_group<T, E>, safe_sectors_view<T, E>>;

	sources_t sources;
	build_result<T, E> results;
	ctpl::thread_pool pool;

	static const unsigned int worker_count;

	// Populate sources with default values so that no call to operator[]
	// invalidates iterators or modifies the container.
	// Required before calling build_safe
	template <class InputIt>
	void populate(InputIt first, InputIt last);

	// Build a solution (thread-safe)
	// results member is not used. Instead, a variable is returned from this function
	// [warn] Call populate on all elements before calling this
	template <class InputIt>
	build_result<T, E> build_safe(InputIt first, InputIt last);
public:
	// Constructors ===========================================================
	level_builder();

	level_builder(const level_builder& other) = delete;
	level_builder(level_builder&& other) = delete;

	// Build a level from a container
	template <class Container, class = std::enable_if_t<
		zh::is_range_v<Container> &&
		std::is_same_v<typename Container::value_type, cluster<T, E>>>>
	bool build(const Container& last_level);

	// Build a level from two iterators.
	// Optional parameter accepts container size, if using
	// std::distance is undesireable
	template <class InputIt>
	bool build(InputIt first, InputIt last, std::size_t size);
	template <class InputIt>
	bool build(InputIt first, InputIt last);

	build_result<T, E>& result() noexcept;
	const build_result<T, E>& result() const noexcept;
};

} // namespace zh

#include "level_builder_mthread.inl"