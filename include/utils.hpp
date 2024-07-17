#pragma once
#include <chrono>
#include <cstdint>
namespace chip_8::utils {

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

/// @brief Returns the time difference in microseconds between two time points.
/// @param start start time point
/// @param end end time point
/// @return time difference in microseconds
inline int64_t timediff_us(TimePoint start, TimePoint end);

};  // namespace chip_8::utils