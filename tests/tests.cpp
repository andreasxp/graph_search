#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <zh/graph_search.hpp>

TEST_CASE("Unit.BasicUsage") {
	zh::graph<int> g1;
	g1.reserve(3);

	auto g1n1 = g1.emplace(1);
	auto g1n2 = g1.emplace(2);
	auto g1n3 = g1.emplace(3);

	g1.connect(g1n1, g1n2);
	g1.connect(g1n2, g1n3);
	g1.connect(g1n3, g1n1);

	zh::graph<int> g2 = g1;
	
	auto result = search(g1, g2);
	CHECK(result.size() == 1);
}

TEST_CASE("Unit.CustomCompare") {
	zh::graph<int> g1;
	g1.reserve(3);

	auto g1n1 = g1.emplace(1);
	auto g1n2 = g1.emplace(2);
	auto g1n3 = g1.emplace(3);

	g1.connect(g1n1, g1n2);
	g1.connect(g1n2, g1n3);
	g1.connect(g1n3, g1n1);

	zh::graph<int> g2 = g1;
	g2.front() = 10;
	
	auto result = search(g1, g2, [](auto&, auto&) {return true;});
	CHECK(result.size() == 1);
}
