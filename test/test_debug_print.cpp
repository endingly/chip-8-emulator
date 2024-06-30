#include <gtest/gtest.h>

#include "chip_8.hpp"

TEST(Chip8, DebugPrint) {
  using namespace chip_8;
  chip_8::Chip8System chip8;
  chip8.print_state();
}