#include <iostream>
#include <string>
#include <zh/test_search.hpp>

using namespace zh;

int main() {
	auto g1 = graph<std::string>::from_adjlist("examples/data/fb.adjlist");
	auto g2 = graph<std::string>::k(4);

	test_search(g1, g2);
}