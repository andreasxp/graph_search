#pragma once
#include <ska/bytell_hash_map.hpp>
#include "../cluster.hpp"

namespace zh {

template <class T>
class build_result : public ska::bytell_hash_set<cluster<T>, sector_nodes_hash<T>, sector_nodes_equal<T>> {
public:
	void add(const cluster<T>& rslt);
	void join(const build_result& other);
};

} // namespace zh

#include "build_result.inl"