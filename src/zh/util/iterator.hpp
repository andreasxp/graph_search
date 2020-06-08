#pragma once
#include <type_traits>
#include <iterator>

#include <zh/type_traits.hpp>

namespace zh {

// advance --------------------------------------------------------------------
// An extension to advance: adds an optional 'limit' parameter. Advance n steps
// or until limit is reached.
template <class InputIt, class Distance>
constexpr void advance(InputIt& it, Distance n);

template <class InputIt, class Distance>
constexpr bool advance(InputIt& it, InputIt limit, Distance n);

// next -----------------------------------------------------------------------
// Implementation of next using zh::advance.
template <class InputIt>
constexpr InputIt next(InputIt it,
	typename std::iterator_traits<InputIt>::difference_type n = 1);

template <class InputIt>
constexpr InputIt next(InputIt it, InputIt limit,
	typename std::iterator_traits<InputIt>::difference_type n = 1);

// prev -----------------------------------------------------------------------
// Implementation of prev using zh::advance.
template <class BidirIt>
constexpr BidirIt prev(BidirIt it,
	typename std::iterator_traits<BidirIt>::difference_type n = 1);

template <class BidirIt>
constexpr BidirIt prev(BidirIt it, BidirIt limit,
	typename std::iterator_traits<BidirIt>::difference_type n = 1);

// select_from ----------------------------------------------------------------
// Select a random iterator in range [first, last), optional generator.
// Behavior is undefined if first is equal to last.
template <class InputIt>
InputIt select_from(InputIt first, InputIt last);

template <class InputIt, class Gen>
InputIt select_from(InputIt first, InputIt last, Gen&& gen);

// Select a random iterator in container, optional generator.
template <class Container, class = std::enable_if_t<
	zh::is_range_v<Container> &&
	zh::has_size_v<Container>>>
auto select_from(Container&& cont);

template <class Container, class Gen, class = std::enable_if_t<
	zh::is_range_v<Container> &&
	zh::has_size_v<Container>>>
auto select_from(Container&& cont, Gen && gen);

} // namespace zh

#include "iterator.inl"