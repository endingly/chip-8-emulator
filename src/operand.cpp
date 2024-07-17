#include "operand.hpp"

#include <cstdlib>
#include <cstring>

chip_8::Chip8System* chip_8::Operand::system = chip_8::Chip8System::get_instance();

const std::map<chip_8::OperandType, chip_8::ISA_Function> chip_8::Operand::isa_set = {
    {chip_8::OperandType::_0NNN, call},
    {chip_8::OperandType::_00E0, clear_screen},
    {chip_8::OperandType::_00EE, return_subroutine},
    {chip_8::OperandType::_1NNN, jump_to_address},
    {chip_8::OperandType::_2NNN, call_subroutine},
    {chip_8::OperandType::_3XNN, skip_if_equal},
    {chip_8::OperandType::_4XNN, skip_if_not_equal},
    {chip_8::OperandType::_5XY0, skip_if_register_equal},
    {chip_8::OperandType::_6XNN, set_register},
    {chip_8::OperandType::_7XNN, add_to_register},
    {chip_8::OperandType::_8XY0, set_register_by_register},
    {chip_8::OperandType::_8XY1, bitwise_or},
    {chip_8::OperandType::_8XY2, bitwise_and},
    {chip_8::OperandType::_8XY3, bitwise_xor},
    {chip_8::OperandType::_8XY4, add_to_register_by_register},
    {chip_8::OperandType::_8XY5, subtract_from_register_by_register},
    {chip_8::OperandType::_8XY6, shift_right},
    {chip_8::OperandType::_8XY7, subtract_from_register},
    {chip_8::OperandType::_8XYE, shift_left},
    {chip_8::OperandType::_9XY0, skip_if_not_equal_register},
    {chip_8::OperandType::_ANNN, set_index},
    {chip_8::OperandType::_BNNN, jump_to_address_plus_v0},
    {chip_8::OperandType::_CXNN, set_register_to_random_number},
    {chip_8::OperandType::_DXYN, draw_sprite},
    {chip_8::OperandType::_EX9E, skip_if_key_pressed},
    {chip_8::OperandType::_EXA1, skip_if_key_not_pressed},
    {chip_8::OperandType::_FX07, set_delay_timer},
    {chip_8::OperandType::_FX0A, wait_for_key_press},
    {chip_8::OperandType::_FX15, set_sound_timer},
    {chip_8::OperandType::_FX18, set_sound_timer},
    {chip_8::OperandType::_FX1E, add_to_index},
    {chip_8::OperandType::_FX29, set_index_to_sprite_address},
    {chip_8::OperandType::_FX33, store_bcd},
    {chip_8::OperandType::_FX55, store_registers},
    {chip_8::OperandType::_FX65, load_registers}};

/// ***************************** Implementation of the ISA set ********************************************/
inline void chip_8::Operand::call(uint16_t value) { system->program_counter = (value & 0x0FFF); }

inline void chip_8::Operand::clear_screen(uint16_t value) {
  std::memset(system->screen, 0, sizeof(system->screen));
  system->chip8_draw_flag = true;
  system->program_counter += 2;
}

inline void chip_8::Operand::return_subroutine(uint16_t value) {
  system->program_counter = system->stack[system->stack_pointer--];
}

inline void chip_8::Operand::jump_to_address(uint16_t value) { system->program_counter = (value & 0x0FFF); }

inline void chip_8::Operand::call_subroutine(uint16_t value) {
  system->stack[++system->stack_pointer] = system->program_counter + 2;
}

inline void chip_8::Operand::skip_if_equal(uint16_t value) {
  system->program_counter += system->V[(value & 0x0F00) >> 8] == (value & 0x00FF) ? 4 : 2;
}

inline void chip_8::Operand::skip_if_not_equal(uint16_t value) {
  system->program_counter += system->V[(value & 0x0F00) >> 8] != (value & 0x00FF) ? 4 : 2;
}

inline void chip_8::Operand::skip_if_register_equal(uint16_t value) {
  system->program_counter += system->V[(value & 0x0F00) >> 8] == system->V[(value & 0x00F0) >> 4] ? 4 : 2;
}

inline void chip_8::Operand::set_register(uint16_t value) {
  system->V[(value & 0x0F00) >> 8] = (value & 0x00FF);
  system->program_counter += 2;
}

inline void chip_8::Operand::add_to_register(uint16_t value) {
  system->V[(value & 0x0F00) >> 8] += (value & 0x00FF);
  system->program_counter += 2;
}

inline void chip_8::Operand::set_register_by_register(uint16_t value) {
  system->V[(value & 0x0F00) >> 8] = system->V[(value & 0x00F0) >> 4];
}

inline void chip_8::Operand::bitwise_or(uint16_t value) {
  system->V[(value & 0x0F00) >> 8] |= system->V[(value & 0x00F0) >> 4];
}

inline void chip_8::Operand::bitwise_and(uint16_t value) {
  system->V[(value & 0x0F00) >> 8] &= system->V[(value & 0x00F0) >> 4];
}

inline void chip_8::Operand::bitwise_xor(uint16_t value) {
  system->V[(value & 0x0F00) >> 8] ^= system->V[(value & 0x00F0) >> 4];
}

inline void chip_8::Operand::add_to_register_by_register(uint16_t value) {
  system->V[0xF] = int(system->V[(value & 0x0F00) >> 8]) + int(system->V[(value & 0x00F0) >> 4]) > 255 ? 1 : 0;
  system->V[(value & 0x0F00) >> 8] += system->V[(value & 0x00F0) >> 4];
}

inline void chip_8::Operand::subtract_from_register_by_register(uint16_t value) {
  system->V[0xF] = system->V[(value & 0x0F00) >> 8] > system->V[(value & 0x00F0) >> 4] ? 1 : 0;
  system->V[(value & 0x0F00) >> 8] -= system->V[(value & 0x00F0) >> 4];
}

inline void chip_8::Operand::shift_right(uint16_t value) {
  system->V[0xF] = system->V[(value & 0x0F00) >> 8] & 0x01;
  system->V[(value & 0x0F00) >> 8] >>= 1;
}

inline void chip_8::Operand::subtract_from_register(uint16_t value) {
  system->V[0xF]                   = system->V[(value & 0x00F0) >> 4] > system->V[(value & 0x0F00) >> 8] ? 1 : 0;
  system->V[(value & 0x0F00) >> 8] = system->V[(value & 0x00F0) >> 4] - system->V[(value & 0x0F00) >> 8];
}

inline void chip_8::Operand::shift_left(uint16_t value) {
  system->V[0xF] = (system->V[(value & 0x0F00) >> 8] & 0x80) >> 7;
  system->V[(value & 0x0F00) >> 8] <<= 1;
}

inline void chip_8::Operand::skip_if_not_equal_register(uint16_t value) {
  system->program_counter += system->V[(value & 0x0F00) >> 8] != system->V[(value & 0x00F0) >> 4] ? 4 : 2;
}

inline void chip_8::Operand::set_index(uint16_t value) {
  system->index_register = (value & 0x0FFF);
  system->program_counter += 2;
}

inline void chip_8::Operand::jump_to_address_plus_v0(uint16_t value) {
  system->program_counter = (value & 0x0FFF) + system->V[0];
}

inline void chip_8::Operand::set_register_to_random_number(uint16_t value) {
  system->V[(value & 0x0F00) >> 8] = (std::rand() % 256) & (value & 0x00FF);
}

inline void chip_8::Operand::draw_sprite(uint16_t value) {
  uint8_t x = system->V[(value & 0x0F00) >> 8];
  uint8_t y = system->V[(value & 0x00F0) >> 4];
  uint8_t n = (value & 0x000F);

  // implement
  uint32_t row = y, col = x;
  uint32_t byte_index, bit_index;

  // set VF to 0
  system->V[0xF] = 0;

  for (byte_index = 0; byte_index < n; byte_index++) {
    uint8_t byte = system->memory[system->index_register + byte_index];
    for (bit_index = 0; bit_index < 8; bit_index++) {
      uint8_t  bit = (byte >> bit_index) & 0x1;
      uint8_t* pixelp =
          &system->screen[(row + byte_index) * system->SCREEN_HEIGHT][(col + (7 - bit_index)) % system->SCREEN_WIDTH];
      // if drawing to the screen would cause any pixel to be erased,
      // set the collision flag to 1
      if (bit == 1 && *pixelp == 1) system->V[0xF] = 1;
      *pixelp ^= bit;
    }
  }
  system->program_counter += 2;
  system->chip8_draw_flag = true;
}

inline void chip_8::Operand::skip_if_key_pressed(uint16_t value) {
  system->program_counter += system->key[system->V[(value & 0x0F00) >> 8] & 0x00FF] ? 4 : 2;
}

inline void chip_8::Operand::skip_if_key_not_pressed(uint16_t value) {
  system->program_counter += !system->key[system->V[(value & 0x0F00) >> 8] & 0x00FF] ? 4 : 2;
}

inline void chip_8::Operand::set_register_to_delay_timer(uint16_t value) {
  system->V[(value & 0x0F00) >> 8] = system->delay_timer;
  system->program_counter += 2;
}

void chip_8::Operand::wait_for_key_press(uint16_t value) {
  while (true) {
    for (uint32_t i = 0; i < system->KEY_COUNT; i++)
      if (system->key[i]) {
        system->V[(value & 0x0F00) >> 8] = i;
        goto got_key_press;
      }
  }
got_key_press:
  system->program_counter += 2;
}

inline void chip_8::Operand::set_delay_timer(uint16_t value) {
  system->delay_timer = system->V[(value & 0x0F00) >> 8];
  system->program_counter += 2;
}

inline void chip_8::Operand::set_sound_timer(uint16_t value) {
  system->sound_timer = system->V[(value & 0x0F00) >> 8];
  system->program_counter += 2;
}

inline void chip_8::Operand::add_to_index(uint16_t value) {
  system->V[0xF] = (system->index_register + (value & 0x00FF)) > 0xFFF ? 1 : 0;
  system->index_register += system->V[(value & 0x0F00) >> 8];
  system->program_counter += 2;
}

inline void chip_8::Operand::set_index_to_sprite_address(uint16_t value) {
  system->index_register = system->V[(value & 0x0F00) >> 8] * system->FONTSET_BYTES_PER_CHAR;
  system->program_counter += 2;
}

inline void chip_8::Operand::store_bcd(uint16_t value) {
  system->memory[system->index_register]     = (system->V[(value & 0x0F00) >> 8] % 1000) / 100;
  system->memory[system->index_register + 1] = (system->V[(value & 0x0F00) >> 8] % 100) / 10;
  system->memory[system->index_register + 2] = (system->V[(value & 0x0F00) >> 8] % 10);
  system->program_counter += 2;
}

inline void chip_8::Operand::store_registers(uint16_t value) {
  for (uint32_t i = 0; i <= ((value & 0x0F00) >> 8); i++) system->memory[system->index_register + i] = system->V[i];
  system->index_register += ((value & 0x0F00) >> 8) + 1;
  system->program_counter += 2;
}

inline void chip_8::Operand::load_registers(uint16_t value) {
  for (uint32_t i = 0; i <= ((value & 0x0F00) >> 8); i++) system->V[i] = system->memory[system->index_register + i];
  system->index_register += ((value & 0x0F00) >> 8) + 1;
  system->program_counter += 2;
}
