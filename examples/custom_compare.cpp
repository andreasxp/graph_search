#include <iostream>
#include <zh/test_search.hpp>

using namespace zh;

int main() {
	// Using a custom comparator function you can compare graphs with different types, as well as follow different
	// comparison functions.
	graph<int> g1;
	g1.reserve(3);

	auto g1n1 = g1.emplace(1);
	auto g1n2 = g1.emplace(2);
	auto g1n3 = g1.emplace(3);

	g1.connect(g1n1, g1n2);
	g1.connect(g1n2, g1n3);
	g1.connect(g1n3, g1n1);

	graph<char> g2;
	g2.reserve(3);

	auto g2n1 = g2.emplace('a');
	auto g2n2 = g2.emplace('b');
	auto g2n3 = g2.emplace('c');

	g2.connect(g2n1, g2n2);
	g2.connect(g2n2, g2n3);
	g2.connect(g2n3, g2n1);

	// Provide a custom comparator function to compare topology only
	test_search(g1, g2, [](const int& lhs, const char& rhs) {
		return true;
	});
}