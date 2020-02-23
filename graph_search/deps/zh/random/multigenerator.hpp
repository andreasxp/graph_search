#pragma once
#include <random>
#include <type_traits>
#include <limits>
#include <cstdint>

#include "thread_safe_random_device.hpp"

namespace zh {

// A generic generator that creates uniform values of any base type with no
// restrictions. Can be seeded, seeded automatically by a random_device.
class multigenerator {
private:
	inline static thread_safe_random_device rd;

	std::conditional_t<sizeof(std::size_t) == 8,
		std::mt19937_64,
		std::mt19937> mt;

public:
	multigenerator() :
		mt(rd()) {
	}

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

inline void multigenerator::seed(unsigned int s) {
	mt.seed(s);
}

inline void multigenerator::seed() {
	mt.seed(rd());
}

template<class T>
inline T multigenerator::get() {
	return get(
		std::numeric_limits<T>::lowest(),
		std::numeric_limits<T>::max()
	);
}

template<class T>
inline T multigenerator::get(T min, T max) {
	if constexpr (
		std::is_same_v<T, bool> ||
		std::is_same_v<T, char> ||
		std::is_same_v<T, signed char> ||
		std::is_same_v<T, unsigned char> ||
		std::is_same_v<T, std::int8_t> ||
		std::is_same_v<T, std::uint8_t>) {
		return static_cast<T>(get<int>(min, max));
	}
	else if constexpr (std::is_integral_v<T>) {
		std::uniform_int_distribution<T> dist(min, max);
		return dist(mt);
	}
	else if constexpr (std::is_floating_point_v<T>) {
		// uniform_real_distribution requires that max-min <= std::numeric_limits<T>::max()
		// to check that without overflow need to divide by 2
		if (max / 2 - min / 2 > std::numeric_limits<T>::max() / 2) {
			bool which_half = get<bool>();
			T half = (max / 2) - (min / 2);

			std::uniform_real_distribution<T> dist_lower_half(min, min + half);
			T result = dist_lower_half(mt);

			return which_half ? result : result + half;
		}

		std::uniform_real_distribution<T> dist(min, max);
		return dist(mt);
	}
}

} // namespace zh