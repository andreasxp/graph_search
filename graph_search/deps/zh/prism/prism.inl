#pragma once
#include "prism.hpp"

namespace zh {

// Member functions ===========================================================
// Casting --------------------------------------------------------------------
template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr prism<C, It, CIt, RIt, CRIt, IArgs>::operator fprism<C, It, CIt>&() noexcept {
	// The inheritance diagram for the prism family looks like this:
	//
	//        cfprism
	//        /     \
	//    cprism   fprism   
	//        \
	//         prism
	//
	// Since only cfprism contains data members, we can use reinterpret_cast
	// to safely cast prism to fprism.
	return reinterpret_cast<fprism<C, It, CIt>&>(*this);
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr prism<C, It, CIt, RIt, CRIt, IArgs>::operator const fprism<C, It, CIt>&() const noexcept {
	return reinterpret_cast<const fprism<C, It, CIt>&>(*this);
}

// Iterators ------------------------------------------------------------------
template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr It prism<C, It, CIt, RIt, CRIt, IArgs>::begin() noexcept {
	using std::make_from_tuple;
	using std::make_tuple;
	using std::tuple_cat;

	return make_from_tuple<It>(
		tuple_cat(make_tuple(this->base().begin()), this->args()));
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr CIt prism<C, It, CIt, RIt, CRIt, IArgs>::begin() const noexcept {
	return base_type::begin();
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr It prism<C, It, CIt, RIt, CRIt, IArgs>::end() noexcept {
	using std::make_from_tuple;
	using std::make_tuple;
	using std::tuple_cat;

	return make_from_tuple<It>(
		tuple_cat(make_tuple(this->base().end()), this->args()));
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr CIt prism<C, It, CIt, RIt, CRIt, IArgs>::end() const noexcept {
	return base_type::end();
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr RIt prism<C, It, CIt, RIt, CRIt, IArgs>::rbegin() noexcept {
	return RIt(this->base().end());
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr CRIt prism<C, It, CIt, RIt, CRIt, IArgs>::rbegin() const noexcept {
	return base_type::rbegin();
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr RIt prism<C, It, CIt, RIt, CRIt, IArgs>::rend() noexcept {
	return RIt(this->base().begin());
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr CRIt prism<C, It, CIt, RIt, CRIt, IArgs>::rend() const noexcept {
	return base_type::rend();
}

// Element access -------------------------------------------------------------
template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr decltype(auto) prism<C, It, CIt, RIt, CRIt, IArgs>::front() {
	return *begin();
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr decltype(auto) prism<C, It, CIt, RIt, CRIt, IArgs>::front() const {
	return *begin();
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr decltype(auto) prism<C, It, CIt, RIt, CRIt, IArgs>::back() {
	return *rbegin();
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr decltype(auto) prism<C, It, CIt, RIt, CRIt, IArgs>::back() const {
	return *rbegin();
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr decltype(auto) prism<C, It, CIt, RIt, CRIt, IArgs>::operator[](difference_type offset) {
	return begin()[offset];
}

template<class C, class It, class CIt, class RIt, class CRIt, class IArgs>
constexpr decltype(auto) prism<C, It, CIt, RIt, CRIt, IArgs>::operator[](difference_type offset) const {
	return begin()[offset];
}

} // namespace zh