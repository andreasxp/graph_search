#pragma once
#include <iostream>
#include "cluster.hpp"
#include "zh/util/assert.hpp"

namespace zh {

template<class T>
template<class U, class F>
graph_match cluster<T>::search(const cluster<U>& other, F&& compare) const {
	//Sectors must be of one size
	GS_ASSERT(nodes.size() == other.nodes.size());

	if (nodes.size() == 1) {
		auto& v1 = (*nodes.begin())->value();
		auto& v2 = (*other.nodes.begin())->value();

		if (!compare(v1, v2)) return {}; //Exit 2a: Values are different

		//std::cout << "Sectors " << *this << " and " << other << " conform" << std::endl;
		//std::cin.get();

		graph_match rslt;
		rslt.add((*nodes.begin())->id(), (*other.nodes.begin())->id());
		//std::cout << "And return this: " << rslt << std::endl;
		return rslt;
	}
	else {
		if (!std::equal(nodes.begin(), nodes.end(), other.nodes.begin(),
			[&compare](auto&& n1, auto&& n2) {
				return compare(n1->value(), n2->value());
			})) return {}; //Exit 2b: Values are different

		//std::cout << "Sectors " << *this << " and " << other << " conform so far" << std::endl;
		//std::cin.get();

		graph_match rslt;
		//In the following loop, i represents this->children, and j - other.children
		//For each j, there must be an equivalent i. So if i reaches end() before j
		//return failure
		for (auto i = children.begin(), j = other.children.begin(); j != other.children.end(); i++, j++) {
			if (i == children.end()) {
				//std::cout << "Sectors " << *this << " and " << other << " failed on children! 3a" << std::endl;
				return {};
			}; //Exit 3a: Children not conformant

			graph_match temp;
			while (!(temp = (*i)->search(**j, compare))) {
				i++;
				if (i == children.end()) {
					//std::cout << "Sectors " << *this << " and " << other << " failed on children! 3b" << std::endl;
					return {};
				}//Exit 3a: Children not conformant
			}
			rslt += temp;
		}

		//std::cout << "Sectors " << *this << " and " << other << " fully conform! 0" << std::endl;
		//std::cout << "And return this: " << rslt << std::endl;
		return rslt; //Exit 0: Success
	}
}

template<class T>
cluster<T>& cluster<T>::join_children(const cluster& other) {
	GS_ASSERT(nodes == other.nodes);

	children.insert(other.children.begin(), other.children.end());

	return *this;
}

template<class T>
std::size_t cluster<T>::size_in_bytes() const {
	return
		nodes.size() * sizeof(node<T>*) +
		children.size() * sizeof(cluster*);
}

template<class T>
cluster<T>::cluster(const node<T>& nd) :
	nodes({&nd}) {
}

template<class T>
cluster<T>::cluster(const cluster& sec, const node<T>& nd) :
	nodes(sec.nodes),
	children({&sec}) {
	nodes.insert(&nd);
	// Assert that this node was not already in the cluster
	GS_ASSERT(nodes.size() == sec.nodes.size() + 1);
}

template<class T>
cluster<T>::cluster(const cluster& child1, const cluster& child2) :
	nodes(child1.nodes) {
	// Children must have identical node_groups except for one node.
	GS_ASSERT(child1.nodes.size() == child2.nodes.size());

	//nodes.insert(child1.nodes.begin(), child1.nodes.end());
	nodes.insert(child2.nodes.begin(), child2.nodes.end());

	// Children must have identical node_groups except for one node.
	GS_ASSERT(nodes.size() == child1.nodes.size() + 1);

	children.insert(&child1);
	children.insert(&child2);
}

template<class T> bool operator==(const cluster<T> & lhs, const cluster<T> & rhs) { return lhs.nodes == rhs.nodes && lhs.children == rhs.children; }
template<class T> bool operator!=(const cluster<T> & lhs, const cluster<T> & rhs) { return !operator==(lhs, rhs); }
template<class T> bool operator< (const cluster<T> & lhs, const cluster<T> & rhs) { return lhs.nodes < rhs.nodes; }
template<class T> bool operator> (const cluster<T> & lhs, const cluster<T> & rhs) { return  operator< (rhs, lhs); }
template<class T> bool operator<=(const cluster<T> & lhs, const cluster<T> & rhs) { return !operator> (lhs, rhs); }
template<class T> bool operator>=(const cluster<T> & lhs, const cluster<T> & rhs) { return !operator< (lhs, rhs); }

template <class T>
std::ostream& operator<<(std::ostream & os, const cluster<T> & obj) {
	os << "{";

	for (auto&& i : obj.nodes) {
		os << *i;
	}

	os << "}";

	return os;
}

} // namespace zh