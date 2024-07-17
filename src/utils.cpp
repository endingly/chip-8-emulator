#include "utils.hpp"

int64_t chip_8::utils::timediff_us(TimePoint start, TimePoint end) {
  return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}
