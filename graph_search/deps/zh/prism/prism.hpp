#pragma once
#include <cstdint>
#include <iterator>
#include "cprism.hpp"
#include "fprism.hpp"

namespace zh {

template <
	class C,
	class It,
	class CIt,
	class RIt  = std::reverse_iterator<It>,
	class CRIt = std::reverse_iterator<CIt>,
	class IArgs = std::tuple<>>
class prism : public cprism<C, CIt, CRIt, IArgs> {
private:
	using base_type = cprism<C, CIt, CRIt, IArgs>;

public:
	// Member types ===========================================================
	using value_type      = typename std::iterator_traits<It>::value_type;
	using reference       = typename std::iterator_traits<It>::reference;
	using const_reference = typename std::iterator_traits<CIt>::reference;
	using pointer         = typename std::iterator_traits<It>::pointer;
	using const_pointer   = typename std::iterator_traits<CIt>::pointer;

	using size_type       = std::size_t;
	using difference_type = typename std::iterator_traits<It>::difference_type;

	using iterator               = It;
	using const_iterator         = CIt;
	using reverse_iterator       = RIt;
	using const_reverse_iterator = CRIt;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	using base_type::base_type;

	// Casting ----------------------------------------------------------------
	// The inheritance diagram for the prism family looks like this:
	//
	//        cfprism
	//        /     \
	//    cprism   fprism   
	//        \
	//         prism
	//
	// To enable casting prism to fprism without implementing virtual bases,
	// the following implicit cast is added.
	constexpr operator fprism<C, It, CIt>&() noexcept;
	constexpr operator const fprism<C, It, CIt>&() const noexcept;

	// Iterators --------------------------------------------------------------
	constexpr It  begin() noexcept;
	constexpr CIt begin() const noexcept;
	// cbegin inherited

	constexpr It  end() noexcept;
	constexpr CIt end() const noexcept;
	// cend inherited

	constexpr RIt  rbegin() noexcept;
	constexpr CRIt rbegin() const noexcept;
	// crbegin inherited

	constexpr RIt  rend() noexcept;
	constexpr CRIt rend() const noexcept;
	// crend inherited

	// Element access ---------------------------------------------------------
	constexpr decltype(auto) front();
	constexpr decltype(auto) front() const;

	constexpr decltype(auto) back();
	constexpr decltype(auto) back() const;

	constexpr decltype(auto) operator[](difference_type offset);
	constexpr decltype(auto) operator[](difference_type offset) const;

	// Capacity methods inherited
};

} // namespace zh

#include "prism.inl"