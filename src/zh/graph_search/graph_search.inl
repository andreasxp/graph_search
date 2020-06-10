#pragma once
#include <utility>
#include "graph_search.hpp"
#include "puff.hpp"

namespace zh {

template<class T, class U, class F>
std::set<match<T, U>> search(const graph<T>& source, const graph<U>& target, F&& compare) {
	puff target_puff(target);
	puff source_puff(source, target_puff.depth());

	return source_puff.search(target_puff, std::forward<F>(compare));
}

template<class T>
bool operator==(const graph<T>& lhs, const graph<T>& rhs) {
	return puff(lhs) == puff(rhs);
}

template<class T>
bool operator!=(const graph<T>& lhs, const graph<T>& rhs) {
	return !(lhs == rhs);
}

} // namespace zh