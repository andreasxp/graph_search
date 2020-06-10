#pragma once
#include <mutex>
#include "../cluster.hpp"

namespace zh {

template <class T>
struct safe_clusters_view {
	mutable std::mutex rwmutex;
	std::vector<const cluster<T>*> sectors;

	constexpr safe_clusters_view() = default;

	safe_clusters_view(const safe_clusters_view& other);
	safe_clusters_view(safe_clusters_view&& other) = default;

	safe_clusters_view& operator=(const safe_clusters_view& other);
	safe_clusters_view& operator=(safe_clusters_view&& other) = default;
};

} // namespace zh

#include "safe_clusters_view.inl"
