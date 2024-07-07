/// @copyright (c) 2024 endingly
/// @author endingly
/// @file chip_8.hpp
/// @brief This file contains the main class for the CHIP-8 emulator.

#pragma once
#include <cstdint>
#include <string>

namespace chip_8 {

struct Chip8System {
  // CHIP-8 system constants
  static constexpr uint32_t MEMORY_MAX_SIZE        = 4096;
  static constexpr uint32_t REGISTER_COUNT         = 16;
  static constexpr uint32_t STACK_MAX_SIZE         = 16;
  static constexpr uint32_t SCREEN_WIDTH           = 64;
  static constexpr uint32_t SCREEN_HEIGHT          = 32;
  static constexpr uint32_t KEY_COUNT              = 16;
  static constexpr uint32_t SCREEN_SIZE            = SCREEN_WIDTH * SCREEN_HEIGHT;
  static constexpr uint32_t FONTSET_START_ADDRESS  = 0x00;
  static constexpr uint32_t FONTSET_BYTES_PER_CHAR = 5;
  static constexpr uint8_t  chip8_fontset[80]      = {
      0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
      0x20, 0x60, 0x20, 0x20, 0x70,  // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
      0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
      0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
      0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
      0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
      0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
      0xF0, 0x80, 0xF0, 0x80, 0x80   // F
  };

  // CHIP-8 system variables
  uint8_t  memory[MEMORY_MAX_SIZE];
  uint8_t  V[REGISTER_COUNT];
  uint16_t operand;
  uint16_t index_register;
  uint16_t program_counter;
  uint8_t  screen[SCREEN_WIDTH][SCREEN_HEIGHT];
  uint8_t  delay_timer;
  uint8_t  sound_timer;
  uint8_t  stack[STACK_MAX_SIZE];
  uint8_t  stack_pointer;
  uint8_t  key[KEY_COUNT];
  bool     chip8_draw_flag;

 public:
  /// @brief the function to initialize the CHIP-8 system
  void initialize();
  void loadgame(const std::string& game_file_path);
  void emulate_cycle();
  void set_keys();
  /// @brief the function to tick the timer of beep sound
  void                tick();
  void                print_state();
  static Chip8System* get_instance();

 private:
  static Chip8System* instance;
  Chip8System()  = default;
  ~Chip8System() = default;
};

}  // namespace chip_8
