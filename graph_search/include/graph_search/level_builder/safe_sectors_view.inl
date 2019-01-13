#pragma once
#include "safe_sectors_view.hpp"

template<class T>
inline safe_sectors_view<T>::safe_sectors_view(const safe_sectors_view& other) {
	std::unique_lock lk(other.rwmutex);
	sectors = other.sectors;
}

template<class T>
inline safe_sectors_view<T>& safe_sectors_view<T>::operator=(const safe_sectors_view& other) {
	std::unique_lock lk(other.rwmutex);
	sectors = other.sectors;
	return *this;
}