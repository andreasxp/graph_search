#pragma once
#include "graph.hpp"

namespace zh {

template<class T, class E>
std::ostream& operator<<(std::ostream& os, const graph<T, E>& obj) {
	os << "nodes: {";

	const char* separator = "\n";
	for (auto&& nd : obj.nodes()) {
		os << separator << "    " << nd;
		separator = ",\n";
	}

	os << "\n},\nedges: {";
	separator = "\n";
	for (auto&& nd : obj.edges()) {
		os << separator << "    " << nd;
		separator = ",\n";
	}
	os << "\n}";

	return os;
}

template<class T, class E>
void swap(graph<T, E>& lhs, graph<T, E>& rhs) noexcept {
	// enable ADL
	using std::swap;

	swap(lhs.m_nodes, rhs.m_nodes);
}

} // namespace zh