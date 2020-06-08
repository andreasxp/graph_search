#pragma once
#include "level_builder.hpp"

#include <zh/type_traits.hpp>
#include "build_result.hpp"

namespace zh {

template <class T, class E>
class level_builder<T, E, false> {
private:
	using sources_t = ska::bytell_hash_map<node_group<T, E>, std::vector<const cluster<T, E>*>>;

	sources_t sources;
	build_result<T, E> results;

public:
	// Build a level from a container
	template <class Container, class = std::enable_if_t<
		zh::is_range_v<Container> &&
		std::is_same_v<typename Container::value_type, cluster<T, E>>>>
		bool build(const Container& last_level);

	template <class InputIt>
	bool build(InputIt first, InputIt last);

	build_result<T, E>& result() noexcept;
	const build_result<T, E>& result() const noexcept;
};

} // namespace zh

#include "level_builder_1thread.inl"