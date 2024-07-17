#include "chip_8.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>

#include "operand.hpp"

chip_8::Chip8System* chip_8::Chip8System::instance = nullptr;

void chip_8::Chip8System::print_state() {
  std::printf("-----------------------current state------------------------------\n");
  std::printf("V0: 0x%02x  V4: 0x%02x  V8: 0x%02x  VC: 0x%02x\n", V[0], V[4], V[8], V[12]);
  std::printf("V1: 0x%02x  V5: 0x%02x  V9: 0x%02x  VD: 0x%02x\n", V[1], V[5], V[9], V[13]);
  std::printf("V2: 0x%02x  V6: 0x%02x  VA: 0x%02x  VE: 0x%02x\n", V[2], V[6], V[10], V[14]);
  std::printf("V3: 0x%02x  V7: 0x%02x  VB: 0x%02x  VF: 0x%02x\n", V[3], V[7], V[11], V[15]);
  std::printf("\n");
  std::printf("PC: 0x%04x\n", program_counter);
}

void chip_8::Chip8System::initialize() {
  this->program_counter = 0x200;  // Start at 0x200
  this->operand         = 0;
  this->index_register  = 0;
  this->stack_pointer   = 0;
  chip8_draw_flag       = true;
  delay_timer           = 0;
  sound_timer           = 0;

  std::memset(this->memory, 0, MEMORY_MAX_SIZE);
  std::memset(this->V, 0, REGISTER_COUNT);
  std::memset(this->stack, 0, STACK_MAX_SIZE);
  std::memset(this->screen, 0, SCREEN_SIZE);
  std::memset(this->key, 0, KEY_COUNT);

  // Load font set into memory
  std::memcpy((this->memory) + FONTSET_START_ADDRESS, chip8_fontset, 80);

  std::srand(std::time(nullptr));
}

void chip_8::Chip8System::loadgame(const std::string& game_file_path) {
  std::fstream file;
  file.open(game_file_path, std::ios::in | std::ios::binary);
  if (!file.is_open()) {
    std::printf("Failed to open file: %s\n", game_file_path.c_str());
    return;
  }
  file.read((char*)this->memory + 0x200, MEMORY_MAX_SIZE - 0x200);
  file.close();
}

void chip_8::Chip8System::emulate_cycle() {
#ifdef DEBUG
  printf("PC: 0x%04x Op: 0x%04x\n", PC, opcode);
#endif
  // Fetch Opcode
  Operand opcode =
      static_cast<Operand>((this->memory[this->program_counter] << 8) | this->memory[this->program_counter + 1]);
  opcode.Do();
#ifdef DEBUG
  this->print_state();
#endif
}

void chip_8::Chip8System::tick() {
  // update timers
  if (delay_timer > 0) {
    --delay_timer;
  }
  if (sound_timer > 0) {
    --sound_timer;
    if (sound_timer == 0) {
      std::printf("BEEP!\n");
    }
  }
}
