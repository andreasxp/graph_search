#pragma once
#include <mutex>
#include <random>

class thread_safe_random_device {
private:
	std::mutex mx;
	std::random_device rd;

public:
	thread_safe_random_device() = default;

	thread_safe_random_device(const thread_safe_random_device& other) = delete;
	thread_safe_random_device(thread_safe_random_device&& other) = delete;

	inline auto operator()();
};

inline auto thread_safe_random_device::operator()() {
	std::lock_guard lg(mx);
	return rd();
}
