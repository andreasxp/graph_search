#pragma once
#include <type_traits>
#include <utility>
#include <iterator>
#include "enable_if_defined.hpp"

namespace zh {

template <class T, class Enable1 = void, class Enable2 = void>
struct is_range : std::false_type {
};

template <class T>
struct is_range<T,
	enable_if_defined_t<decltype(std::begin(std::declval<T&>()))>,
	enable_if_defined_t<decltype(std::end(std::declval<T&>()))>> : std::true_type {
};

template <class T>
constexpr bool is_range_v = is_range<T>::value;

} // namespace zh