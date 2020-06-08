#include <iostream>
#include <zh/graph_search.hpp>
#include <zh/graph.hpp>

using namespace zh;

int main() {
	graph<int> g1;
	g1.reserve(4);

	auto g1n1 = g1.emplace(1);
	auto g1n2 = g1.emplace(1);
	auto g1n3 = g1.emplace(2);
	auto g1n4 = g1.emplace(3);

	g1.connect(g1n1, g1n3);
	g1.connect(g1n2, g1n3);
	g1.connect(g1n3, g1n4);
	g1.connect(g1n1, g1n4);

	graph<int> g2;
	g2.reserve(3);

	auto g2n1 = g2.emplace(1);
	auto g2n2 = g2.emplace(2);
	auto g2n3 = g2.emplace(3);

	g2.connect(g2n1, g2n2);
	g2.connect(g2n2, g2n3);
	g2.connect(g2n1, g2n3);

	puff pf1(g1);
	puff pf2(g2);

	std::cout << "puff 1:" << pf1 << "\n";
	std::cout << "puff 2:" << pf2 << "\n";
}