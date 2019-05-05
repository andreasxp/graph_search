#pragma once
#include "deps/zh/random.hpp"

struct test_gen {
	generator<int> gen;

	int operator()() {
		return gen(0, 5);
	}
};

namespace zh {

template <>
class generator<std::monostate> {
public:
	std::monostate operator()() {
		return std::monostate{};
	}
};

}