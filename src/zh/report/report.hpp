#pragma once
#include <string>
#include <initializer_list>
#include <zh/graph.hpp>
#include "zh/graph_search/puff.hpp"
#include "zh/util/json.hpp"

namespace zh {

template <
	class Range1 = std::initializer_list<int>,
	class Range2 = std::initializer_list<int>,
	class Range3 = std::initializer_list<double>>
	void report(const std::string & save_path,
		const Range1 & sizes,
		const Range2 & depths,
		const Range3 & ratios,
		int attempts = 5);

template <class T, class E>
json info(const graph<T, E>& gr);

template <class T, class E>
json info(const puff<T, E>& pf) {
	json j;

	j["puff_size"] = pf.depth();
	j["puff_clusters"] = pf.count_sectors();
	j["puff_edges"] = pf.count_edges();
	j["puff_size_in_bytes"] = pf.size_in_bytes();

	return j;
}

template <
	class T, class E,
	class R1 = std::initializer_list<std::size_t>,
	class R2 = std::initializer_list<std::size_t>,
	class R3 = std::initializer_list<double>,
	class F>
	json report2(
		const R1& sizes,
		const R2& max_depths,
		const R3& ratios,
		std::size_t attempts,
		F&& callable);


} // namespace zh

#include "report.inl"