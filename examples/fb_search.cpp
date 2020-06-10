#include <iostream>
#include <string>
#include <variant>
#include <zh/test_search.hpp>

using namespace zh;

int main() {
	auto g1 = graph<std::string>::from_adjlist("examples/data/fb.adjlist");
	auto g2 = graph<int>::k(4);

	auto topology_only = [](auto&&, auto&&) {
		return true;
	};

	auto mappings = search(g1, g2, topology_only);

	for (auto&& mapping : mappings) {
		auto separator = "";
		for (auto&& pair : mapping) {
			std::cout << separator << pair.second->value();
			separator = ", ";
		}

		std::cout << "\n";
	}
}