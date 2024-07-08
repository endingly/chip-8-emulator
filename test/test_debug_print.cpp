#include <gtest/gtest.h>

#include "chip_8.hpp"
#include "operand.hpp"

TEST(Chip8, DebugPrint) {
  using namespace chip_8;
  auto chip8 = chip_8::Chip8System::get_instance();
  chip8->print_state();
}

TEST(Operand, DebugPrint) {
  using namespace chip_8;
  auto operand = chip_8::Operand(0x1234);
  std::cout << sizeof(operand) << std::endl;
}