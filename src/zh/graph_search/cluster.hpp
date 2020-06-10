#pragma once
#include <algorithm>
#include <set>
#include <boost/container/flat_set.hpp>

#include "functors/sector_functors.hpp"
#include "node_group.hpp"
#include "graph_match.hpp"
using boost::container::flat_set;

namespace zh {

template <class T>
class cluster {
public:
	node_group<T, void> nodes;
	flat_set<const cluster*, sector_lexicographical_order<T>> children;

	template<class U, class F>
	graph_match search(const cluster<U>& other, F&& compare = F()) const;
	cluster& join_children(const cluster& other);
	std::size_t size_in_bytes() const;

	constexpr cluster() = default;
	cluster(const cluster& other) = default;
	// Create a cluster from one node
	explicit cluster(const node<T>& nd);
	// Construct a cluster by expanding a cluster by one node
	cluster(const cluster& sec, const node<T>& nd);
	// Construct a cluster by merging two sectors and setting them as children.
	// This assumes that children have identical node_groups except for one node.
	cluster(const cluster& child1, const cluster& child2);
};

template<class T> bool operator==(const cluster<T>& lhs, const cluster<T>& rhs);
template<class T> bool operator!=(const cluster<T>& lhs, const cluster<T>& rhs);
template<class T> bool operator< (const cluster<T>& lhs, const cluster<T>& rhs);
template<class T> bool operator> (const cluster<T>& lhs, const cluster<T>& rhs);
template<class T> bool operator<=(const cluster<T>& lhs, const cluster<T>& rhs);
template<class T> bool operator>=(const cluster<T>& lhs, const cluster<T>& rhs);

template <class T>
std::ostream& operator<<(std::ostream& os, const cluster<T>& obj);

} // namespace zh

#include "cluster.inl"