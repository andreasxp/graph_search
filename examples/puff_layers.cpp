#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
#include <zh/graph_search.hpp>
#include <zh/mutate.hpp>
#include <zh/graph.hpp>

using namespace zh;
using json = nlohmann::json;

int main() {
	graph<int> g;
	mutate_nodes(g, 20);
	mutate_edges(g, 0.2);

	puff pf(g);

	for (std::size_t i = 0; i < pf.depth(); i++) {
		std::cout << pf[i].size() << std::endl;
	}
}