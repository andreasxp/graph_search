#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include "zh/util/json.hpp"
#include "graph_search.hpp"
namespace fs = std::filesystem;

template<class T, class U, class F = std::equal_to<void>>
void test_search(const zh::graph<T>& graph1, const zh::graph<U>& graph2, F&& compare = F()) {
	auto mapping = search(graph1, graph2, compare);

	std::cout
		<< "= Graph info ===================================================================" << std::endl
		<< "graph 1: " << graph1 << std::endl
		<< "graph 2: " << graph2 << std::endl
		<< std::endl
		<< "= Results ======================================================================" << std::endl
		<< "Answer: graph 1 " << (!mapping.empty() ? "contains" : "does not contain") << " graph 2" << std::endl;

	if (!mapping.empty()) {
		std::cout << "Results:" << std::endl;
		for (auto&& i : mapping) {
			std::cout << "map " << i << std::endl;
		}
	}

	std::ofstream ofs("last_test.json");
	json j;
	j["graph 1"] = graph1;
	j["graph 2"] = graph2;
	ofs << std::setw(4) << j;
	ofs.close();
}

void test_search(const fs::path& file) {
	std::ifstream ifs(file);
	json j;
	ifs >> j;

	zh::graph<int> graph1 = j["graph 1"];
	zh::graph<int> graph2 = j["graph 2"];

	test_search(graph1, graph2);
}