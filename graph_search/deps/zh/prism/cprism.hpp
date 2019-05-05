#pragma once
#include <cstdint>
#include "cfprism.hpp"

namespace zh {

template <
	class C,
	class CIt,
	class CRIt = std::reverse_iterator<CIt>,
	class IArgs = std::tuple<>>
class cprism : public cfprism<C, CIt, IArgs> {
private:
	using base_type = cfprism<C, CIt, IArgs>;

public:
	// Member types ===========================================================
	using value_type      = typename std::iterator_traits<CIt>::value_type;
	using reference       = typename std::iterator_traits<CIt>::reference;
	using const_reference = typename std::iterator_traits<CIt>::reference;
	using pointer         = typename std::iterator_traits<CIt>::pointer;
	using const_pointer   = typename std::iterator_traits<CIt>::pointer;

	using size_type       = std::size_t;
	using difference_type = typename std::iterator_traits<CIt>::difference_type;

	using iterator               = CIt;
	using const_iterator         = CIt;
	using reverse_iterator       = CRIt;
	using const_reverse_iterator = CRIt;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	using base_type::base_type;

	// Iterators --------------------------------------------------------------
	// begin inherited
	// cbegin inherited

	// end inherited
	// cend inherited

	constexpr CRIt rbegin() const noexcept;
	constexpr CRIt crbegin() const noexcept;

	constexpr CRIt rend() const noexcept;
	constexpr CRIt crend() const noexcept;

	// Element access ---------------------------------------------------------
	// front inherited

	constexpr decltype(auto) back() const;

	// operator[] inherited

	// Capacity methods inherited
};

} // namespace zh

#include "cprism.inl"