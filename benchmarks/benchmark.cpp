#include <benchmark/benchmark.h>
#include <fstream>
#include <filesystem>
#include <string>
#include "zh/util/json.hpp"
#pragma comment(lib, "shlwapi.lib") // MSVC++ does not work without this

#include "zh/benchmark.hpp"
#include "deps/zh/type_traits.hpp"
#include "zh/util/generator.hpp"
#include "zh/graph_search.hpp"
#include "zh/mutate.hpp"

namespace fs = std::filesystem;

// Fix google macros to support namespaces, templates, and binds ==============
#define ZH_BENCHMARK_PRIVATE_NAME \
	BENCHMARK_PRIVATE_CONCAT(_benchmark_, BENCHMARK_PRIVATE_UNIQUE_ID, 0)

#define ZH_BENCHMARK_PRIVATE_DECLARE \
	static ::benchmark::internal::Benchmark* ZH_BENCHMARK_PRIVATE_NAME \
		BENCHMARK_UNUSED

#define ZH_BENCHMARK(...) \
	ZH_BENCHMARK_PRIVATE_DECLARE = \
		(::benchmark::internal::RegisterBenchmarkInternal( \
		new ::benchmark::internal::FunctionBenchmark(#__VA_ARGS__, __VA_ARGS__)))

#define ZH_BENCHMARK_BIND(...) \
	ZH_BENCHMARK_PRIVATE_DECLARE = \
		(::benchmark::internal::RegisterBenchmarkInternal( \
		new ::benchmark::internal::FunctionBenchmark(#__VA_ARGS__, \
		[](benchmark::State& state){__VA_ARGS__;})))

// ============================================================================
namespace { // internal linkage

// Generate a random graph
template <std::size_t graph_size, class GraphRatio>
void graph_creation(benchmark::State& state) {
	static_assert(zh::is_ratio_v<GraphRatio>, "benchmark: GraphRatio is not a valid ratio");
	double graph_ratio = static_cast<double>(GraphRatio::type::num) / GraphRatio::type::den;

	auto monogen = [] () { return std::monostate {}; };

	for (auto _ : state) {
		zh::graph<std::monostate> x;
		zh::mutate_nodes(x, graph_size, monogen);
		zh::mutate_edges(x, graph_ratio);
	}
}

// Generate a random graph, then create a puff with specified max_depth
// Default depth is maximum possible depth
template <
	std::size_t graph_size, class GraphRatio,
	std::size_t max_depth = static_cast<std::size_t>(-1)>
void puff_creation(benchmark::State& state) {
	static_assert(zh::is_ratio_v<GraphRatio>, "benchmark: GraphRatio is not a valid ratio");
	double graph_ratio = static_cast<double>(GraphRatio::type::num) / GraphRatio::type::den;

	for (auto _ : state) {
		zh::graph<int> g;
		mutate_nodes(g, graph_size, test_gen());
		mutate_edges(g, graph_ratio);
		zh::puff pf(g, max_depth);
	}
}

// Load a graph from file, then create a puff with specified max_depth
// Default depth is maximum possible depth
template <std::size_t max_depth = static_cast<std::size_t>(-1)>
void puff_creation(benchmark::State& state, const fs::path& file) {
	std::ifstream ifs(file);
	json j;
	ifs >> j;
	zh::graph<int> g = j;

	for (auto _ : state) {
		zh::puff pf(g, max_depth);
	}
}

// Search for a subgraph in a graph
template <
	std::size_t graph_size, class GraphRatio,
	std::size_t subgraph_size, class SubgraphRatio>
void graph_search(benchmark::State& state) {
	static_assert(zh::is_ratio_v<GraphRatio>, "benchmark: GraphRatio is not a valid ratio");
	static_assert(zh::is_ratio_v<SubgraphRatio>, "benchmark: SubgraphRatio is not a valid ratio");

	double graph_ratio = static_cast<double>(GraphRatio::type::num) / GraphRatio::type::den;
	double subgraph_ratio = static_cast<double>(SubgraphRatio::type::num) / SubgraphRatio::type::den;

	auto monogen = [] () { return std::monostate {}; };

	for (auto _ : state) {
		zh::graph<std::monostate> x;
		zh::mutate_nodes(x, graph_size, monogen);
		zh::mutate_edges(x, graph_ratio);
		
		zh::graph<std::monostate> y;
		zh::mutate_nodes(y, subgraph_size, monogen);
		zh::mutate_edges(y, subgraph_ratio);

		benchmark::DoNotOptimize(search(x, y));
	}
}

void graph_search(benchmark::State& state, const fs::path& file) {
	auto monogen = [] () { return 0; };

	zh::graph<int> sub;
	zh::mutate_nodes(sub, 3, monogen);
	zh::mutate_edges(sub, 1);

	std::ifstream ifs(file);
	json j;
	ifs >> j;
	zh::graph<int> g = j;

	zh::puff sub_pf(sub);
	zh::puff pf(g, sub_pf.depth());

	for (auto _ : state) {
		benchmark::DoNotOptimize(pf.search(sub_pf));
	}
}

} // namespace

// Active benchmarks ==========================================================
//ZH_BENCHMARK(graph_creation<10, std::ratio<2, 10>>);
//ZH_BENCHMARK(puff_creation<10, std::ratio<2, 10>, 3>);

ZH_BENCHMARK_BIND(puff_creation(state, "bench/graph-15-0.2.json"))
->Unit(benchmark::kMillisecond)
->MinTime(60);
ZH_BENCHMARK_BIND(puff_creation(state, "bench/graph-15-0.4.json"))
->Unit(benchmark::kMillisecond)
->MinTime(60);
ZH_BENCHMARK_BIND(puff_creation(state, "bench/graph-15-0.6.json"))
->Unit(benchmark::kMillisecond)
->MinTime(60);
ZH_BENCHMARK_BIND(puff_creation(state, "bench/graph-20-0.2.json"))
->Unit(benchmark::kMillisecond)
->MinTime(60);

/*ZH_BENCHMARK(graph_creation<20, std::ratio<6, 10>>)
->Unit(benchmark::kMicrosecond);
ZH_BENCHMARK(graph_creation<3, std::ratio<1>>)
->Unit(benchmark::kMicrosecond);
ZH_BENCHMARK(graph_search<20, std::ratio<6, 10>, 3, std::ratio<1>>)
->Unit(benchmark::kMicrosecond);
*/

// ============================================================================
int run_benchmark(int argc, char** argv) {
	benchmark::Initialize(&argc, argv);
	if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
	benchmark::RunSpecifiedBenchmarks();
	return 0;
}