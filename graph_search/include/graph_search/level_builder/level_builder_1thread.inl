#pragma once
#include "level_builder_1thread.hpp"

template<class T>
template<class Container, class>
inline bool level_builder<T, false>::build(const Container& last_level) {
	return build(std::begin(last_level), std::end(last_level));
}

template<class T>
template<class InputIt>
inline bool level_builder<T, false>::build(InputIt first, InputIt last) {
	GS_ASSERT(first->nodes.size() >= 2);
	sources.clear();
	results.clear();

	// For each sector in last level
	for (InputIt it = first; it != last; ++it) {
		const sector<T>& sector = *it;
		// Go over each possible part of its group
		// (see node_group::except_1)
		for (auto& part : sector.nodes.except_1()) {
			// Example: sector is abc, part is ac
			// In sources[part], go over all values, build a new sector with
			// each of them, and insert each one into results
			for (auto& source : sources[part]) {
				results.add({sector, *source});
			}
			// Finally, add this sector to sources
			sources[part].push_back(&sector);
		}
	}

	if (results.empty()) return false;
	return true;
}

template<class T>
inline build_result<T>& level_builder<T, false>::result() noexcept {
	return results;
}

template<class T>
inline const build_result<T>& level_builder<T, false>::result() const noexcept {
	return results;
}