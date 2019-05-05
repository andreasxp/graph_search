#pragma once
#include <map>
#include <set>
#include <utility>
#include "zh/util/pretty_print.hpp"

class graph_match {
private:
	std::map<std::size_t, std::size_t> matches;
public:
	inline void add(std::size_t first, std::size_t second);

	inline graph_match& operator+=(const graph_match& rhs);

	inline explicit operator bool();

	friend inline bool operator==(const graph_match& lhs, const graph_match& rhs);
	friend inline bool operator< (const graph_match& lhs, const graph_match& rhs);

	friend inline std::ostream& operator<<(std::ostream& os, const graph_match& obj);
};

inline graph_match::operator bool() {
	return !matches.empty();
}

inline bool operator==(const graph_match& lhs, const graph_match& rhs) {
	return lhs.matches == rhs.matches;
}

inline bool operator!=(const graph_match& lhs, const graph_match& rhs) {
	return !(lhs == rhs);
}

inline bool operator< (const graph_match& lhs, const graph_match& rhs) {
	return lhs.matches < rhs.matches;
}

inline bool operator> (const graph_match& lhs, const graph_match& rhs) {
	return rhs < lhs;
}

inline bool operator<=(const graph_match& lhs, const graph_match& rhs) {
	return !(rhs < lhs);
}

inline bool operator>=(const graph_match& lhs, const graph_match& rhs) {
	return !(lhs < rhs);
}

inline void graph_match::add(std::size_t first, std::size_t second) {
	matches[first] = second;
}

inline graph_match& graph_match::operator+=(const graph_match & rhs) {
	matches.insert(rhs.matches.begin(), rhs.matches.end());

	return *this;
}

inline graph_match operator+(graph_match lhs, const graph_match& rhs) {
	lhs += rhs;
	return lhs;
}

inline std::ostream& operator<<(std::ostream& os, const graph_match& obj) {
	os << "{" << std::endl;

	for (auto i : obj.matches) {
		os << "    {#" << pretty(i.first) << " - #" << pretty(i.second) << "}" << std::endl;
	}

	os << "}";

	return os;
}

inline std::set<graph_match> merge(const std::set<graph_match>& v1, const std::set<graph_match>& v2) {
	if (v1.empty()) return v2;
	if (v2.empty()) return v1;

	std::set<graph_match> rslt;

	//Merge
	for (auto&& i : v1) {
		for (auto&& j : v2) {
			rslt.emplace(i + j);
		}
	}

	return rslt;
}