#pragma once
#include "deps/ska/flat_hash_map.hpp"
#include "../connection/connection.hpp"
#include "functors.hpp"

namespace zh {
namespace detail {

template <class T, class E>
using node_container = ska::flat_hash_set<
	connection<T, E>,
	connection_node_hash<T, E>,
	connection_node_equal<T, E, node_id_equal>>;

}
}