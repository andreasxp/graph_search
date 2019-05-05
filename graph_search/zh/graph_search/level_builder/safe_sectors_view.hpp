#pragma once
#include <mutex>
#include "../cluster.hpp"

namespace zh {

template <class T, class E>
struct safe_sectors_view {
	mutable std::mutex rwmutex;
	std::vector<const cluster<T, E>*> sectors;

	constexpr safe_sectors_view() = default;

	safe_sectors_view(const safe_sectors_view& other);
	safe_sectors_view(safe_sectors_view&& other) = default;

	safe_sectors_view& operator=(const safe_sectors_view& other);
	safe_sectors_view& operator=(safe_sectors_view&& other) = default;
};

} // namespace zh

#include "safe_sectors_view.inl"
