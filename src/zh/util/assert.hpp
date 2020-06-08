#pragma once
#include <cassert>

#if defined(_DEBUG) or not defined(NDEBUG)
#define GS_ASSERT(...) assert((__VA_ARGS__))
#else
#define GS_ASSERT(...) do {} while (0)
#endif