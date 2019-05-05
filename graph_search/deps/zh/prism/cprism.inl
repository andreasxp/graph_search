#pragma once
#include "cprism.hpp"

namespace zh {

// Member functions ===========================================================
// Iterators ------------------------------------------------------------------
template<class C, class CIt, class CRIt, class IArgs>
constexpr CRIt cprism<C, CIt, CRIt, IArgs>::rbegin() const noexcept {
	return CRIt(this->end());
}

template<class C, class CIt, class CRIt, class IArgs>
constexpr CRIt cprism<C, CIt, CRIt, IArgs>::crbegin() const noexcept {
	return CRIt(this->cend());
}

template<class C, class CIt, class CRIt, class IArgs>
constexpr CRIt cprism<C, CIt, CRIt, IArgs>::rend() const noexcept {
	return CRIt(this->begin());
}

template<class C, class CIt, class CRIt, class IArgs>
constexpr CRIt cprism<C, CIt, CRIt, IArgs>::crend() const noexcept {
	return CRIt(this->cbegin());
}

// Element access -------------------------------------------------------------
template<class C, class CIt, class CRIt, class IArgs>
constexpr decltype(auto) cprism<C, CIt, CRIt, IArgs>::back() const {
	return *crbegin();
}

} // namespace zh