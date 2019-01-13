#include <iostream>
#include <limits>
#include "benchmark.hpp"
#include "tests.hpp"

int main(int argc, char** argv) {
	using node_iterator = graph<int>::node_iterator;

	graph<int> g;
	g.reserve(2);

	auto nd1 = g.emplace(101);
	std::cout << *nd1 << '\n';
	auto nd2 = g.emplace(102);
	std::cout << *nd2 << '\n';

	g.connect(nd1, nd2);

	auto nd3 = g.emplace(103);
	std::cout << *nd3 << '\n';
	auto nd4 = g.emplace(104);
	std::cout << *nd4 << '\n';
	auto nd5 = g.emplace(105);
	std::cout << *nd5 << '\n';

	std::cout << "graph has " << g.size() << " nodes: {\n";
	for (auto&& nd : g.nodes()) {
		std::cout << "    " << nd << " -> ";
		for (auto&& adj : nd.adjacent_nodes()) {
			std::cout << adj << " ";
		}
		std::cout << "\n";
	}
	std::cout << "}" << std::endl;
	

	/*
	std::ifstream ifs("graph-20-0.2.json");
	json j;
	ifs >> j;
	graph<int> g = j;

	puff pf(g);

	for (std::size_t i = 0; i < pf.depth(); i++) {
		std::cout << pf[i].size() << std::endl;
	}*/

	//run_benchmark(argc, argv);
	//test_search("last_test.json");

	/*graph<int> g;
	mutate(g, 15, 0.6, test_gen());

	std::ofstream ofs("graph-15-0.6.json");
	json j = g;
	ofs << std::setw(4) << j;*/

	std::cout << "Done." << std::endl;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}