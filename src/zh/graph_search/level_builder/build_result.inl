#pragma once
#include "build_result.hpp"

namespace zh {

template<class T>
void build_result<T>::add(const cluster<T>& rslt) {
	auto [it, insert_happened] = this->insert(rslt);

	if (!insert_happened) {
		// If insertion did not take place, just join children
		it->join_children(rslt);
	}
}

template<class T>
void build_result<T>::join(const build_result& other) {
	for (const auto& sec : other) {
		add(sec);
	}
}

} // namespace zh