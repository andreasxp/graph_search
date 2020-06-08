#pragma once
#include "safe_sectors_view.hpp"

namespace zh {

template<class T, class E>
safe_sectors_view<T, E>::safe_sectors_view(const safe_sectors_view& other) {
	std::unique_lock lk(other.rwmutex);
	sectors = other.sectors;
}

template<class T, class E>
safe_sectors_view<T, E>& safe_sectors_view<T, E>::operator=(const safe_sectors_view& other) {
	std::unique_lock lk(other.rwmutex);
	sectors = other.sectors;
	return *this;
}

} // namespace zh