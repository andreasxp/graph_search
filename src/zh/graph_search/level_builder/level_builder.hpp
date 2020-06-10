#pragma once

namespace zh {

// Builds one level of a puff
template <class T, bool is_multithreaded = true>
class level_builder;

} // namespace zh

// Specializations are exposed here
#include "level_builder_1thread.hpp"
#include "level_builder_mthread.hpp"