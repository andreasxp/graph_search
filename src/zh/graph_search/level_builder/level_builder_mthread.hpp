#pragma once
#include "level_builder.hpp"

#include <ska/bytell_hash_map.hpp>
#include <zh/graph.hpp>
#include "deps/ctpl_stl.h"

#include "../node_group.hpp"
#include "safe_clusters_view.hpp"
#include "build_result.hpp"

namespace zh {

template <class T>
class level_builder<T, true> {
private:
	using sources_t = ska::bytell_hash_map<node_group<T, void>, safe_clusters_view<T>>;

	sources_t sources;
	build_result<T> results;
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
	build_result<T> build_safe(InputIt first, InputIt last);
public:
	// Constructors ===========================================================
	level_builder();

	level_builder(const level_builder& other) = delete;
	level_builder(level_builder&& other) = delete;

	// Build a level from a container
	template <class Container, class = std::enable_if_t<
		zh::is_range_v<Container> &&
		std::is_same_v<typename Container::value_type, cluster<T>>>>
	bool build(const Container& last_level);

	// Build a level from two iterators.
	// Optional parameter accepts container size, if using
	// std::distance is undesireable
	template <class InputIt>
	bool build(InputIt first, InputIt last, std::size_t size);
	template <class InputIt>
	bool build(InputIt first, InputIt last);

	build_result<T>& result() noexcept;
	const build_result<T>& result() const noexcept;
};

} // namespace zh

#include "level_builder_mthread.inl"