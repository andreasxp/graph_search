#pragma once
#include <cstdint>
#include "deps/zh/graph.hpp"
#include "zh/graph_search/puff.hpp"
#include "zh/util/json.hpp"

namespace zh {

struct data_unit {
	// Keys
	std::size_t graph_size = 0;
	std::size_t max_puff_depth = 0;
	double target_graph_ratio = 1;

	// Data
	double graph_ratio = 1;
	double puff_depth = 0;
	double puff_edges = 0;
	double puff_sectors = 0;
	std::size_t averaged_over = 0;

	constexpr data_unit() = default;

	template <class T>
	data_unit(const graph<T>& gr, std::size_t max_depth, double target_ratio = -1);

	void merge(const data_unit& du);
};

void from_json(const json& j, data_unit& du);
void to_json(json& j, const data_unit& du);

} // namespace zh

#include "data_unit.inl"
