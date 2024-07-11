
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <chrono>
#include <iostream>
#include <map>

#include "chip_8.hpp"

// variables
chip_8::Chip8System*                                  chip8System = chip_8::Chip8System::get_instance();
static std::chrono::high_resolution_clock::time_point clock_prev;
constexpr int                                         SCREEN_PIXELS = 5;
constexpr int                                         BLACK         = 0;
constexpr int                                         WHITE         = 255;
constexpr int                                         PIXEL_SIZE    = 5;
constexpr int                                         SCREEN_ROWS   = chip8System->SCREEN_HEIGHT * PIXEL_SIZE;
constexpr int                                         SCREEN_COLS   = chip8System->SCREEN_WIDTH * PIXEL_SIZE;
const static std::map<unsigned char, int>             key_map       = {
    {'1', 0x1}, {'2', 0x2}, {'3', 0x3}, {'4', 0xc}, {'q', 0x4}, {'w', 0x5}, {'e', 0x6}, {'r', 0xd},
    {'a', 0x7}, {'s', 0x8}, {'d', 0x9}, {'f', 0xe}, {'z', 0xa}, {'x', 0x0}, {'c', 0xb}, {'v', 0xf},
};

void keypress(unsigned char k, int x, int y) {
  (void)x;
  (void)y;
  int index = key_map.at(k);
  if (index >= 0) {
    chip8System->key[index] = 1;
  }
}

void keyrelease(unsigned char k, int x, int y) {
  (void)x;
  (void)y;
  int index = key_map.at(k);
  if (index >= 0) {
    chip8System->key[index] = 0;
  }
}

/// @brief Calculate time difference
/// @param now now time point
/// @param prev previous time point
/// @return time difference in microseconds
inline int64_t timediff_us(std::chrono::high_resolution_clock::time_point now,
                           std::chrono::high_resolution_clock::time_point prev) {
  return std::chrono::duration_cast<std::chrono::microseconds>(now - prev).count();
}

inline void paint_pixel(int row, int col, unsigned char color) {
  row                           = chip8System->SCREEN_HEIGHT - 1 - row;
  chip8System->screen[row][col] = chip8System->screen[row][col] = chip8System->screen[row][col] = color;
}

void paint_cell(int row, int col, unsigned char color) {
  int pixel_row = row * PIXEL_SIZE;
  int pixel_col = col * PIXEL_SIZE;
  int drow, dcol;
  for (drow = 0; drow < PIXEL_SIZE; drow++) {
    for (dcol = 0; dcol < PIXEL_SIZE; dcol++) {
      paint_pixel(pixel_row + drow, pixel_col + dcol, color);
    }
  }
}

void gfx_setup() {
  memset(chip8System->screen, BLACK, sizeof(unsigned char) * SCREEN_ROWS * SCREEN_COLS * 3);
  glClear(GL_COLOR_BUFFER_BIT);
}

void draw() {
  // Clear framebuffer
  glClear(GL_COLOR_BUFFER_BIT);
  // Draw pixels to the buffer
  for (int row = 0; row < chip8System->SCREEN_WIDTH; row++) {
    for (int col = 0; col < chip8System->SCREEN_HEIGHT; col++) {
      paint_cell(row, col, chip8System->screen[row][col] ? WHITE : BLACK);
    }
  }

  // Update Texture
  glDrawPixels(SCREEN_COLS, SCREEN_ROWS, GL_RGB, GL_UNSIGNED_BYTE, (void*)chip8System->screen);
  glutSwapBuffers();
}

void reshape_window(GLsizei w, GLsizei h) {
  (void)w;
  (void)h;
}

void loop() {
  // Get current time
  auto clock_now                 = std::chrono::high_resolution_clock::now();
  clock_prev                     = clock_now;
  static const int CLOCK_RATE_MS = 1000 / 60;

  chip8System->emulate_cycle();

  if (chip8System->chip8_draw_flag) {
    draw();
    chip8System->chip8_draw_flag = false;
  }

  int64_t timediff = timediff_us(clock_now, clock_prev);
  // if time difference is greater than CLOCK_RATE_MS, then we neeed tick the emulator
  if (timediff > CLOCK_RATE_MS) {
    // tick emulator
    chip8System->tick();
    clock_prev = clock_now;
  }
}

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
  glutMainLoop();

  // start emulator loop
  glutDisplayFunc(draw);
  glutIdleFunc(loop);
  glutReshapeFunc(reshape_window);

  glutKeyboardFunc(keypress);
  glutKeyboardUpFunc(keyrelease);

  gfx_setup();

  // gettimeofday(&clock_prev, NULL);

  // Run the emulator
  glutMainLoop();

  return 0;
};