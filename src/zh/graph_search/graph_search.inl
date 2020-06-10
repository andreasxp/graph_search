#pragma once
#include "graph_search.hpp"
#include "puff.hpp"

namespace zh {

template<class T, class E>
std::set<graph_match> search(const graph<T, E>& source, const graph<T, E>& target) {
	std::cout << "Started search\n";
	puff target_puff(target);
	std::cout << "Build target puff with " << target_puff.depth() << " layers\n";
	puff source_puff(source, target_puff.depth());
	std::cout << "Build source puff with " << source_puff.depth() << " layers\n";

	return source_puff.search(target_puff);
}

template<class T, class E>
bool operator==(const graph<T, E>& lhs, const graph<T, E>& rhs) {
	return puff(lhs) == puff(rhs);
}

template<class T, class E>
bool operator!=(const graph<T, E>& lhs, const graph<T, E>& rhs) {
	return !(lhs == rhs);
}

} // namespace zh