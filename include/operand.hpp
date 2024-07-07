#pragma once
#include <functional>
#include <map>

#include "chip_8.hpp"
namespace chip_8 {

/// @brief Enum for the different types of operands in the Chip-8 instruction set.
enum class OperandType : uint16_t {
  _0NNN = 0x0000,
  _00E0 = 0x00E0,
  _00EE = 0x00EE,
  _1NNN = 0x1000,
  _2NNN = 0x2000,
  _3XNN = 0x3000,
  _4XNN = 0x4000,
  _5XY0 = 0x5000,
  _6XNN = 0x6000,
  _7XNN = 0x7000,
  _8XY0 = 0x8000,
  _8XY1 = 0x8001,
  _8XY2 = 0x8002,
  _8XY3 = 0x8003,
  _8XY4 = 0x8004,
  _8XY5 = 0x8005,
  _8XY6 = 0x8006,
  _8XY7 = 0x8007,
  _8XYE = 0x800E,
  _9XY0 = 0x9000,
  _ANNN = 0xA000,
  _BNNN = 0xB000,
  _CXNN = 0xC000,
  _DXYN = 0xD000,
  _EX9E = 0xE09E,
  _EXA1 = 0xE0A1,
  _FX07 = 0xF007,
  _FX0A = 0xF00A,
  _FX15 = 0xF015,
  _FX18 = 0xF018,
  _FX1E = 0xF01E,
  _FX29 = 0xF029,
  _FX33 = 0xF033,
  _FX55 = 0xF055,
  _FX65 = 0xF065
};

/// @brief Base class for all operands in the Chip-8 instruction set.
class Operand {
 private:
  uint16_t                                                          value;
  const static std::map<OperandType, std::function<void(uint16_t)>> isa_set;
  static chip_8::Chip8System*                                       system;

 public:
  Operand() = default;
  Operand(uint16_t value) : value(value) {}
  inline void Do();
  ~Operand() = default;

 private:
  inline static void call(uint16_t value);
  inline static void clear_screen(uint16_t value);
  inline static void return_subroutine(uint16_t value);
  inline static void jump_to_address(uint16_t value);
  inline static void call_subroutine(uint16_t value);
  inline static void skip_if_equal(uint16_t value);
  inline static void skip_if_not_equal(uint16_t value);
  inline static void skip_if_register_equal(uint16_t value);
};

}  // namespace chip_8
