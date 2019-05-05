#pragma once
#include "data_unit_lex_order.hpp"

namespace zh {

inline bool data_unit_lex_order::operator()(const data_unit& lhs, const data_unit& rhs) {
	if (lhs.graph_size < rhs.graph_size) return true;
	else if (lhs.graph_size == rhs.graph_size) {
		if (lhs.max_puff_depth < rhs.max_puff_depth) return true;
		else if (lhs.max_puff_depth == rhs.max_puff_depth) {
			if (lhs.target_graph_ratio < rhs.target_graph_ratio) return true;
		}
	}

	return false;
}

inline bool data_unit_lex_order::operator()(const data_unit& lhs, const std::tuple<std::size_t, std::size_t, double>& rhs) {
	if (lhs.graph_size < std::get<0>(rhs)) return true;
	else if (lhs.graph_size == std::get<0>(rhs)) {
		if (lhs.max_puff_depth < std::get<1>(rhs)) return true;
		else if (lhs.max_puff_depth == std::get<1>(rhs)) {
			if (lhs.target_graph_ratio < std::get<2>(rhs)) return true;
		}
	}

	return false;
}

inline bool data_unit_lex_order::operator()(const std::tuple<std::size_t, std::size_t, double>& lhs, const data_unit& rhs) {
	if (std::get<0>(lhs) < rhs.graph_size) return true;
	else if (std::get<0>(lhs) == rhs.graph_size) {
		if (std::get<1>(lhs) < rhs.max_puff_depth) return true;
		else if (std::get<1>(lhs) == rhs.max_puff_depth) {
			if (std::get<2>(lhs) < rhs.target_graph_ratio) return true;
		}
	}

	return false;
}

} // namespace zh