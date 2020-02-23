#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "zh/mutate.hpp"
#include "report.hpp"
#include "deps/zh/graph.hpp"
#include "zh/graph_search/graph_search.hpp"
#include "zh/util/generator.hpp"
#include "data_pack.hpp"
namespace fs = std::filesystem;

namespace zh {

template <class Range1, class Range2, class Range3>
void report(const std::string& save_path,
	const Range1& sizes,
	const Range2& depths,
	const Range3& ratios,
	int attempts) {

	zh::data_pack data;
	// If file previously existed, append data to existing data
	if (fs::exists(save_path)) {
		std::ifstream ifs(save_path);
		json j;

		ifs >> j;
		data = j;
	}

	for (double p : ratios) {
		for (int k : depths) {
			for (int n : sizes) {
				std::cout << "Computing for "
					<< "target ratio = " << p << ", "
					<< "max depth = " << k << ", "
					<< "size = " << n << std::endl;
				std::cout << "Average over " << attempts << ": ";

				for (int attempt = 1; attempt <= attempts; attempt++) {
					std::cout << attempt << " ";

					zh::graph<int> gr;

					mutate_nodes(gr, n, test_gen());
					mutate_edges(gr, p);

					data.append(gr, k, p);
					data.dump_to_file("_temp_dump.json");
				}

				std::cout << std::endl;
			}
		}
	}

	data.dump_to_file(save_path);
	fs::remove("_temp_dump.json");
}

template <class R>
json merge_entries(const R& entries) {
	std::size_t entry_size = entries.front().size();
	std::size_t attempts = entries.size();

	for (auto&& entry : entries) {
		assert(entry.size() == entry_size);
	}

	json result;
	for (std::size_t property_i = 0; property_i < entry_size; property_i++) {
		for (auto&& entry : entries) {
			auto it = std::next(entry.begin(), property_i);

			result[it.key()].push_back(it.value());
		}
	}

	for (auto&& field : result) {
		double val = field.front();
		for (int i = 1; i < field.size(); i++) {
			val += field[i].get<double>();
		}
		val /= field.size();
		field = val;
	}

	return result;
}

template<class T, class E, class R1, class R2, class R3, class F>
json report2(const R1& sizes, const R2& max_depths, const R3& ratios, std::size_t attempts, F && callable) {
	json data;

	for (auto&& size : sizes) {
		for (auto&& max_depth : max_depths) {
			for (auto&& target_ratio : ratios) {
				std::cout
					<< "Computing for:\n"
					<< "    size = " << size << ";\n"
					<< "    max depth = " << max_depth << ";\n"
					<< "    target ratio = " << target_ratio << ";\n"
					<< "    averaged over = " << attempts << std::endl;

				json entry;
				entry["averaged_over"] = attempts;
				entry["source"]["graph_size"] = size;
				entry["source"]["graph_target_ratio"] = target_ratio;
				entry["source"]["puff_max_depth"] = max_depth;

				std::vector<json> results;
				results.reserve(attempts);

				for (std::size_t attempt = 0; attempt < attempts; attempt++) {
					std::cout << "  attempt " << attempt + 1 << "...";

					zh::graph<T, E> gr;
					mutate_nodes(gr, size, generator<T>{});
					mutate_edges(gr, target_ratio, generator<E>{});

					json result = callable(gr);
					results.push_back(result);

					std::cout << " complete!\n";
				}

				entry["result"] = merge_entries(results);
				data.push_back(entry);
			}
		}
	}

	return data;
}

} // namespace zh