#pragma once
#include <tuple>
#include <cstdint>

namespace zh {

template <
	class C,
	class CIt,
	class IArgs = std::tuple<>> // Additional args to construct an iterator with
class cfprism : private IArgs {
private:
	C& m_data;

protected:
	C&       base() noexcept;
	const C& base() const noexcept;

	IArgs& args() noexcept;
	const IArgs& args() const noexcept;

public:
	// Member types ===========================================================
	using value_type      = typename std::iterator_traits<CIt>::value_type;
	using reference       = typename std::iterator_traits<CIt>::reference;
	using const_reference = typename std::iterator_traits<CIt>::reference;
	using pointer         = typename std::iterator_traits<CIt>::pointer;
	using const_pointer   = typename std::iterator_traits<CIt>::pointer;

	using size_type       = std::size_t;
	using difference_type = typename std::iterator_traits<CIt>::difference_type;

	using iterator        = CIt;
	using const_iterator  = CIt;

	// Member functions =======================================================
	// Constructors -----------------------------------------------------------
	constexpr cfprism(C& container, const IArgs& iargs = IArgs());

	// Iterators --------------------------------------------------------------
	constexpr CIt begin() const noexcept;
	constexpr CIt cbegin() const noexcept;

	constexpr CIt end() const noexcept;
	constexpr CIt cend() const noexcept;

	// Element access ---------------------------------------------------------
	constexpr decltype(auto) front() const;

	constexpr decltype(auto) back() const;

	constexpr decltype(auto) operator[](difference_type offset) const;

	// Capacity ---------------------------------------------------------------
	constexpr std::size_t size() const noexcept;
	constexpr bool empty() const noexcept;
};

} // namespace zh

#include "cfprism.inl"