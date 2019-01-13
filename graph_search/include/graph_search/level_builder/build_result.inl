#pragma once
#include "build_result.hpp"

template<class T>
inline void build_result<T>::add(const sector<T>& rslt) {
	auto[it, insert_happened] = this->insert(rslt);

	if (!insert_happened) {
		// If insertion did not take place, just join children
		it->join_children(rslt);
	}
}

template<class T>
inline void build_result<T>::join(const build_result& other) {
	for (const auto& sec : other) {
		add(sec);
	}
}