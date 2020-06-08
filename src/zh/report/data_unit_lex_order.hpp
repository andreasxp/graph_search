#pragma once
#include <tuple>
#include "data_unit.hpp"

namespace zh {

// A sorter for data_units
struct data_unit_lex_order {
	bool operator()(const data_unit& lhs, const data_unit& rhs);
	bool operator()(const data_unit& lhs, const std::tuple<std::size_t, std::size_t, double>& rhs);
	bool operator()(const std::tuple<std::size_t, std::size_t, double>& lhs, const data_unit& rhs);
};

}

#include "data_unit_lex_order.inl"