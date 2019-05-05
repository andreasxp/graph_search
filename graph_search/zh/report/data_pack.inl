#pragma once
#include <algorithm>
#include <fstream>
#include "data_pack.hpp"

namespace zh {

template<class T>
void data_pack::append(const graph<T>& gr, std::size_t max_depth, double target_ratio) {
	data_unit du(gr, max_depth, target_ratio);

	auto got = std::lower_bound(data.begin(), data.end(), du, data_unit_lex_order());

	if (got == data.end() || data_unit_lex_order()(du, *got)) {
		// No similar data_unit in vector
		data.insert(got, du);
	}
	else {
		// Merge with similar
		got->merge(du);
	}
}

data_unit& data_pack::at(std::size_t graph_size, std::size_t max_puff_depth, double graph_ratio) {
	auto key = std::make_tuple(graph_size, max_puff_depth, graph_ratio);

	auto got = std::lower_bound(data.begin(), data.end(), key, data_unit_lex_order());

	if (got == data.end() || data_unit_lex_order()(key, *got)) throw std::invalid_argument("data_pack::at: no such element");
	return *got;
}

std::string data_pack::dump() {
	json j = *this;
	return j.dump(4);
}

void data_pack::dump_to_file(const std::string & file) {
	std::ofstream ofs(file);
	ofs << dump();
}

void from_json(const json & j, data_pack & du) {
	du.data = j.get<std::vector<data_unit>>();
}

void to_json(json & j, const data_pack & du) {
	j = du.data;
}

} // namespace zh