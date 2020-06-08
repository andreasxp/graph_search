#pragma once
#include "level_builder_1thread.hpp"

namespace zh {

template<class T, class E>
template<class Container, class>
bool level_builder<T, E, false>::build(const Container& last_level) {
	return build(std::begin(last_level), std::end(last_level));
}

template<class T, class E>
template<class InputIt>
bool level_builder<T, E, false>::build(InputIt first, InputIt last) {
	GS_ASSERT(first->nodes.size() >= 2);
	sources.clear();
	results.clear();

	// For each cluster in last level
	for (InputIt it = first; it != last; ++it) {
		const cluster<T, E>& cluster = *it;
		// Go over each possible part of its group
		// (see node_group::except_1)
		for (auto& part : cluster.nodes.except_1()) {
			// Example: cluster is abc, part is ac
			// In sources[part], go over all values, build a new cluster with
			// each of them, and insert each one into results
			for (auto& source : sources[part]) {
				results.add({cluster, *source});
			}
			// Finally, add this cluster to sources
			sources[part].push_back(&cluster);
		}
	}

	if (results.empty()) return false;
	return true;
}

template<class T, class E>
build_result<T, E>& level_builder<T, E, false>::result() noexcept {
	return results;
}

template<class T, class E>
const build_result<T, E>& level_builder<T, E, false>::result() const noexcept {
	return results;
}

} // namespace zh