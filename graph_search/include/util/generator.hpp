#pragma once
#include <random>
#include <type_traits>
#include <limits>
#include <cstdint>

constexpr bool is_64bit() {
	return sizeof(size_t) == 8;
}

// Generator that makes any numeric type using get<type>
class multigenerator {
private:
	static inline std::random_device rd;
	std::conditional_t<is_64bit(),
		std::mt19937_64,
		std::mt19937> mt;

public:
	multigenerator();

	multigenerator(const multigenerator& other) = default;
	multigenerator(multigenerator&& other) = default;

	multigenerator& operator=(const multigenerator& other) = default;
	multigenerator& operator=(multigenerator&& other) = default;

	void seed(unsigned int s);
	void seed();

	template <class T>
	T get();

	template <class T>
	T get(T min, T max);
};

// Generator that makes pre-defined types using operator()
template <class T>
struct generator : private multigenerator {
	T operator()(const T& min = std::numeric_limits<T>::lowest(), const T& max = std::numeric_limits<T>::max());
};

struct test_gen {
	generator<int> gen;

	int operator()() {
		return gen(0, 5);
	}
};

#include "inline/generator.inl"