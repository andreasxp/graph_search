#pragma once
#include <type_traits>
#include <string>
#include <sstream>
#include <cmath>

template <class T, class = std::enable_if_t<std::is_pointer_v<T> || std::is_same_v<T, std::size_t>>>
std::string pretty(T ptr, int width = 3) {
	std::stringstream ss;

	ss << std::hex << std::setfill('0');
	if (width > 0) {
		ss << std::setw(width) << static_cast<std::size_t>(ptr) % static_cast<std::size_t>(std::pow(0x10, width));
	}
	else {
		ss << static_cast<std::size_t>(ptr);
	}

	return ss.str();
}