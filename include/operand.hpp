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
  inline static void set_register(uint16_t value);
  inline static void add_to_register(uint16_t value);
  inline static void set_register_by_register(uint16_t value);
  inline static void bitwise_or(uint16_t value);
  inline static void bitwise_and(uint16_t value);
  inline static void bitwise_xor(uint16_t value);
  inline static void add_to_register_by_register(uint16_t value);
  /// @brief `8XY5` - `Vx -= Vy`
  /// @details Subtract the value of a register from another register and store the result in the first register.
  inline static void subtract_from_register_by_register(uint16_t value);
  /// @brief `8XY6` - `Vx >>= 1`
  /// @details Shift the bits of a register to the right by 1.
  inline static void shift_right(uint16_t value);
  /// @brief `8XY7` - `Vx = Vy - Vx`
  /// @details Subtract the value of a register from another register and store the result in the first register.
  inline static void subtract_from_register(uint16_t value);
  /// @brief `8XYE` - `Vx <<= 1`
  /// @details Shift the bits of a register to the left by 1.
  inline static void shift_left(uint16_t value);
  /// @brief `9XY0` - `if(Vx != Vy)`
  /// @details Skip the next instruction if the values of two registers are not equal.
  inline static void skip_if_not_equal_register(uint16_t value);
  /// @brief `ANNN` - `I = nnn`
  /// @details Set the value of the I register to a new address.
  inline static void set_index(uint16_t value);
  /// @brief `BNNN` - `PC = V0 + nnn`
  /// @details Jump to a new address calculated from the current value of the PC register and a constant offset.
  inline static void jump_to_address_plus_v0(uint16_t value);
  /// @brief `CXNN` - `Vx = rand() & nn`
  /// @details Generate a random number between 0 and 255, and store it in a register.
  inline static void set_register_to_random_number(uint16_t value);
  /// @brief `DXYN` - `draw(Vx, Vy, N)`
  /// @details Draw a sprite at position (`Vx`, `Vy`) that has a width of 8 pixels and a height of `N` pixels.
  [[gnu::always_inline]] static void draw_sprite(uint16_t value);
  /// @brief `EX9E` - `if(key() == Vx)`
  /// @details Skip the next instruction if the key corresponding to the value of a register is pressed.
  inline static void skip_if_key_pressed(uint16_t value);
  /// @brief `EXA1` - `if(key() != Vx)`
  /// @details Skip the next instruction if the key corresponding to the value of a register is not pressed.
  inline static void skip_if_key_not_pressed(uint16_t value);
  /// @brief `FX07` - `Vx = delay_timer`
  /// @details Set the value of a register to the value of the delay timer.
  inline static void set_register_to_delay_timer(uint16_t value);
  /// @brief `FX0A` - `Vx = key()`
  /// @details A key press is awaited, and then stored in VX (blocking operation, all instruction halted until next key
  /// event).
  [[gnu::always_inline]] static void wait_for_key_press(uint16_t value);
  /// @brief `FX15` - `delay_timer = Vx`
  /// @details Set the value of the delay timer to the value of a register.
  inline static void set_delay_timer(uint16_t value);
  /// @brief `FX18` - `sound_timer = Vx`
  /// @details Set the value of the sound timer to the value of a register.
  inline static void set_sound_timer(uint16_t value);
  /// @brief `FX1E` - `I += Vx`
  /// @details Add the value of a register to the value of the I register.
  inline static void add_to_index(uint16_t value);
  /// @brief `FX29` - `I = sprite_address[Vx]`
  /// @details Set the value of the I register to the memory address of the sprite corresponding to the value of a
  /// register.
  inline static void set_index_to_sprite_address(uint16_t value);
  /// @brief `FX33` - `BCD(Vx)`
  /// @details Store the binary-coded decimal representation of the value of a register in memory locations I, I+1, and I+2.
  inline static void store_bcd(uint16_t value);
  /// @brief `FX55` - `reg_dump(Vx)`
  /// @details Store the values of registers V0 to Vx in memory starting at address I.
  inline static void store_registers(uint16_t value);
  /// @brief `FX65` - `reg_load(Vx)`
  /// @details Read values from memory starting at address I into registers V0 to Vx.
  inline static void load_registers(uint16_t value);
};

}  // namespace chip_8
