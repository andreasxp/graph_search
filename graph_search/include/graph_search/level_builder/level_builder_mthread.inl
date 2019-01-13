#pragma once
#include "level_builder_mthread.hpp"
#include "deps/zh/iterator.hpp"

template<class T>
const unsigned int level_builder<T, true>::worker_count = std::thread::hardware_concurrency() - 1;

template<class T>
template<class InputIt>
inline void level_builder<T, true>::populate(InputIt first, InputIt last) {
	// For each sector in last level
	for (InputIt it = first; it != last; ++it) {
		const sector<T>& sector = *it;
		// Go over each possible part of its group
		// (see node_group::except_1)
		for (const auto& part : sector.nodes.except_1()) {
			// Populate map with keys
			sources[part];
		}
	}
}

template<class T>
template<class InputIt>
inline build_result<T> level_builder<T, true>::build_safe(InputIt first, InputIt last) {
	build_result<T> rslt;

	// For each sector in last level
	for (InputIt it = first; it != last; ++it) {
		const sector<T>& sector = *it;
		// Go over each possible part of its group
		// (see node_group::except_1)
		for (const auto& part : sector.nodes.except_1()) {
			// Example: sector is abc, part is ac
			// In sources[part], go over all values, build a new sector with
			// each of them, and insert each one into results.

			// Call to sources[part] must not create a new element.
			// Otherwise container will be modified, which is not safe.
			GS_ASSERT(sources.count(part) != 0);
			std::unique_lock lk(sources[part].rwmutex);
			for (auto& source : sources[part].sectors) {
				rslt.add({sector, *source});
			}
			// Finally, add this sector to sources
			sources[part].sectors.push_back(&sector);
		}
	}

	return rslt;
}

template<class T>
template<class Container, class>
inline bool level_builder<T, true>::build(const Container& last_level) {
	return build(std::begin(last_level), std::end(last_level), std::size(last_level));
}

template<class T>
template<class InputIt>
inline bool level_builder<T, true>::build(InputIt first, InputIt last) {
	return build(first, last, std::distance(first, last));
}

template<class T>
template<class InputIt>
inline bool level_builder<T, true>::build(InputIt first, InputIt last, std::size_t size) {
	// For this algorithm to work, sectors must be at least of size 2
	GS_ASSERT(first->nodes.size() >= 2);
	sources.clear();
	results.clear();

	// Populate the sources
	populate(first, last);

	std::vector<std::future<build_result<T>>> async_results;
	async_results.reserve(worker_count);

	// Concurrently compute parts of solution in increments of block_size
	auto block_first = first;
	auto block_last = first;
	std::size_t block_size = static_cast<std::size_t>(std::ceil(
		static_cast<double>(size) / worker_count));

	while (block_last != last) {
		// Move block_first to previous block's block_last
		block_first = block_last;
		// Advance block_last until last is reached
		zh::advance(block_last, last, block_size);

		// Asunc call
		async_results.push_back(pool.push([this, block_first, block_last](int) {
			return this->build_safe(block_first, block_last);
		}));
	}

	// Unpack results and join them
	for (auto& future_rslt : async_results) {
		results.join(future_rslt.get());
	}
	//std::cout << "block_size: " << block_size << "; size: " << async_results.size() << std::endl;
	//std::cin.get();

	if (results.empty()) return false;
	return true;
}

template<class T>
inline level_builder<T, true>::level_builder() :
	pool(worker_count) {
}

template<class T>
inline build_result<T>& level_builder<T, true>::result() noexcept {
	return results;
}

template<class T>
inline const build_result<T>& level_builder<T, true>::result() const noexcept {
	return results;
}