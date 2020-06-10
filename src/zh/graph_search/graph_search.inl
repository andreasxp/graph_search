#pragma once
#include <utility>
#include "graph_search.hpp"
#include "puff.hpp"

namespace zh {

template<class T, class U, class F>
std::set<match<T, U>> search(const graph<T>& source, const graph<U>& target, F&& compare) {
	std::cout << "Started search\n";
	puff target_puff(target);
	std::cout << "Build target puff with " << target_puff.depth() << " layers\n";
	puff source_puff(source, target_puff.depth());
	std::cout << "Build source puff with " << source_puff.depth() << " layers\n";

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