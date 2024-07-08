
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

#include "chip_8.hpp"

constexpr int SCREEN_PIXELS = 5;

int main(int argc, char* argv[]) {
  // check if a game file is provided
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " game_file" << std::endl;
    exit(2);
  }

  // initialize chip-8 emulator
  auto chip8System = chip_8::Chip8System::get_instance();
  chip8System->initialize();
  chip8System->loadgame(argv[1]);

  // initialize graphics
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(chip8System->SCREEN_HEIGHT * SCREEN_PIXELS, chip8System->SCREEN_WIDTH * SCREEN_PIXELS);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("CHIP-8 Emulator");
};