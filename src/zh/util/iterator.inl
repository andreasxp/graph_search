#pragma once
#include "iterator.hpp"

#include <cassert>
#include <random>
#include <zh/random.hpp>

namespace zh {

// advance --------------------------------------------------------------------
template <class InputIt, class Distance>
constexpr void advance(InputIt& it, Distance n) {
	std::advance(it, n);
}

template <class InputIt, class Distance>
constexpr bool advance(InputIt& it, InputIt limit, Distance n) {
	// Case: random_access_iterator
	if constexpr (std::is_same_v<
		std::random_access_iterator_tag,
		typename std::iterator_traits<InputIt>::iterator_category>) {

		if (static_cast<std::size_t>(limit - it) <= n) {
			it = limit;
			return true;
		}
		std::advance(it, n);
		return false;
	}

	// Case: positive offset
	if (n >= 0) {
		for (Distance i = 0; i < n; ++i) {
			++it;
			if (it == limit) return true;
		}

		return false;
	}

	// Case: negative offset
	for (Distance i = 0; i > n; --i) {
		--it;
		if (it == limit) return true;
	}

	return false;
}

// next -----------------------------------------------------------------------
template<class InputIt>
constexpr InputIt next(InputIt it,
	typename std::iterator_traits<InputIt>::difference_type n) {
	advance(it, n);
	return it;
}

template<class InputIt>
constexpr InputIt next(InputIt it, InputIt limit,
	typename std::iterator_traits<InputIt>::difference_type n) {
	advance(it, limit, n);
	return it;
}

// prev -----------------------------------------------------------------------
template<class BidirIt>
constexpr BidirIt prev(BidirIt it,
	typename std::iterator_traits<BidirIt>::difference_type n) {
	advance(it, -n);
	return it;
}

template<class BidirIt>
constexpr BidirIt prev(BidirIt it, BidirIt limit,
	typename std::iterator_traits<BidirIt>::difference_type n) {
	advance(it, limit, -n);
	return it;
}

// select_from ----------------------------------------------------------------
template <class InputIt>
InputIt select_from(InputIt first, InputIt last) {
	assert(first != last);
	std::advance(first, generator<std::size_t>()(0, std::distance(first, last) - 1));
	return first;
}

template <class InputIt, class Gen>
InputIt select_from(InputIt first, InputIt last, Gen && gen) {
	assert(first != last);

	std::uniform_int_distribution<std::size_t> dist(0, std::distance(first, last) - 1);
	std::advance(first, dist(gen));

	return first;
}

template <class Container, class>
auto select_from(Container&& cont) {
// Auto return type to select const_iterator where needed
	assert(std::size(cont) > 0);

	Container& ref = cont;

	return std::next(std::begin(ref),
		generator<std::size_t>()(0, std::size(ref) - 1));
}

template <class Container, class Gen, class>
auto select_from(Container&& cont, Gen&& gen) {
// Auto return type to select const_iterator where needed
	assert(std::size(cont) > 0);

	Container& ref = cont;

	std::uniform_int_distribution<std::size_t> dist(0, std::size(ref) - 1);
	return std::next(std::begin(ref), dist(gen));
}

} // namespace zh