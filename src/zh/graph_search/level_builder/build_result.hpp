#pragma once
#include <ska/bytell_hash_map.hpp>
#include "../cluster.hpp"

namespace zh {

template <class T, class E>
class build_result : public ska::bytell_hash_set<cluster<T, E>, sector_nodes_hash<T, E>, sector_nodes_equal<T, E>> {
public:
	void add(const cluster<T, E>& rslt);
	void join(const build_result& other);
};

} // namespace zh

#include "build_result.inl"