#pragma once
#include "multigenerator.hpp"

namespace zh {

// An adapter for multigenerator with operator()
template <class T>
class generator : private multigenerator {
public:
	T operator()(
		const T& min = std::numeric_limits<T>::lowest(),
		const T& max = std::numeric_limits<T>::max());

	using multigenerator::seed;
};

template<class T>
inline T generator<T>::operator()(const T& min, const T& max) {
	return static_cast<multigenerator&>(*this).get<T>(min, max);
}

} // namespace zh