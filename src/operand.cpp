#include "operand.hpp"

#include <cstring>

chip_8::Chip8System* chip_8::Operand::system = chip_8::Chip8System::get_instance();

const std::map<chip_8::OperandType, std::function<void(uint16_t)>> chip_8::Operand::isa_set = {
    {chip_8::OperandType::_0NNN, call},
    {chip_8::OperandType::_00E0, clear_screen},
    {chip_8::OperandType::_00EE, return_subroutine},
    {chip_8::OperandType::_1NNN, jump_to_address},
    {chip_8::OperandType::_2NNN, call_subroutine},
    {chip_8::OperandType::_3XNN, skip_if_equal},
    {chip_8::OperandType::_4XNN, skip_if_not_equal},
    {chip_8::OperandType::_5XY0, skip_if_register_equal}};

inline void chip_8::Operand::Do() { isa_set.at(static_cast<OperandType>(value))(value); }

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
