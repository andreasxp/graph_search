#include <iostream>
#include <zh/test_search.hpp>

using namespace zh;

int main() {
	graph<int> g1;
	g1.reserve(11);

	auto g1n1  = g1.emplace(6);
	auto g1n2  = g1.emplace(4);
	auto g1n3  = g1.emplace(1);
	auto g1n4  = g1.emplace(3);
	auto g1n5  = g1.emplace(2);
	auto g1n6  = g1.emplace(3);
	auto g1n7  = g1.emplace(1);
	auto g1n8  = g1.emplace(3);
	auto g1n9  = g1.emplace(1);
	auto g1n10 = g1.emplace(2);
	auto g1n11 = g1.emplace(3);

	g1.connect(g1n1,  g1n2);
	g1.connect(g1n2,  g1n3);
	g1.connect(g1n3,  g1n4);
	g1.connect(g1n4,  g1n5);
	g1.connect(g1n5,  g1n6);
	g1.connect(g1n5,  g1n7);
	g1.connect(g1n5,  g1n8);
	g1.connect(g1n6,  g1n7);
	g1.connect(g1n7,  g1n8);
	g1.connect(g1n8,  g1n9);
	g1.connect(g1n9,  g1n10);
	g1.connect(g1n9,  g1n11);
	g1.connect(g1n10, g1n11);

	graph<int> g2;
	g2.reserve(3);

	auto g2n1 = g2.emplace(1);
	auto g2n2 = g2.emplace(2);
	auto g2n3 = g2.emplace(3);

	g2.connect(g2n1, g2n2);
	g2.connect(g2n2, g2n3);
	g2.connect(g2n1, g2n3);

	test_search(g1, g2);
}