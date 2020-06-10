#pragma once
#include "safe_clusters_view.hpp"

namespace zh {

template<class T>
safe_clusters_view<T>::safe_clusters_view(const safe_clusters_view& other) {
	std::unique_lock lk(other.rwmutex);
	sectors = other.sectors;
}

template<class T>
safe_clusters_view<T>& safe_clusters_view<T>::operator=(const safe_clusters_view& other) {
	std::unique_lock lk(other.rwmutex);
	sectors = other.sectors;
	return *this;
}

} // namespace zh