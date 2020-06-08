#pragma once
#include <set>
#include <boost/container/flat_set.hpp>
#include <zh/graph.hpp>
#include "functors/node_functors.hpp"
using boost::container::flat_set;

namespace zh {

template <class T, class E>
class node_group : public flat_set<const node<T, E>*, node_value_order<T, E>> {
private:
	using base_type = flat_set<const node<T, E>*, node_value_order<T, E>>;
public:
	using base_type::base_type;

	// Return a vector of all possible node_groups
	// that are missing one element from *this.
	std::vector<node_group> except_1() const;
};

template<class T, class E>
std::vector<node_group<T, E>> node_group<T, E>::except_1() const {
	std::vector<node_group> rslt;
	rslt.reserve(this->size());

	for (auto not_me = this->begin(); not_me != this->end(); ++not_me) {
		// Emplace with elements left of excluded
		rslt.emplace_back(this->begin(), not_me);
		// Insert element right of excluded
		rslt.back().insert(std::next(not_me), this->end());
	}

	return rslt;
}

} // namespace zh

namespace std {

template <class T, class E>
struct hash<zh::node_group<T, E>> {
	std::size_t operator()(const zh::node_group<T, E>& obj) const {
		std::size_t rslt = 0;

		for (auto& i : obj) {
			rslt ^= hash<const zh::node<T, E>*>()(i);
		}

		return rslt;
	}
};

} // namespace std