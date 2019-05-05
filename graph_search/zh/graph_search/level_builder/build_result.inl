#pragma once
#include "build_result.hpp"

namespace zh {

template<class T, class E>
void build_result<T, E>::add(const cluster<T, E>& rslt) {
	auto [it, insert_happened] = this->insert(rslt);

	if (!insert_happened) {
		// If insertion did not take place, just join children
		it->join_children(rslt);
	}
}

template<class T, class E>
void build_result<T, E>::join(const build_result& other) {
	for (const auto& sec : other) {
		add(sec);
	}
}

} // namespace zh