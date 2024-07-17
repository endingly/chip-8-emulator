#include "monitor.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void chip_8::Monitor::draw_screen() {
  auto system = chip_8::Chip8System::get_instance();
  // Clear framebuffer
  glClear(GL_COLOR_BUFFER_BIT);

  // Draw pixels to the buffer
  for (int row = 0; row < SCREEN_HEIGHT; row++) {
    for (int col = 0; col < SCREEN_WIDTH; col++) {
      paint_cell(row, col, system->screen[row][col] ? WHITE : BLACK);
    }
  }

  // Update Texture
  glDrawPixels(SCREEN_HEIGHT, SCREEN_WIDTH, GL_RGB, GL_UNSIGNED_BYTE, (void *)screen);
  glutSwapBuffers();
}

void chip_8::Monitor::reshape_window(int width, int height) {
  // reshape the window
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

inline void chip_8::Monitor::paint_pixel(int row, int col, ScreenColor color) {
  row                 = SCREEN_HEIGHT - 1 - row;
  screen[row][col][0] = screen[row][col][1] = screen[row][col][2] = color;
}

void chip_8::Monitor::paint_cell(int row, int col, ScreenColor color) {
  int pixel_row = row * PIXEL_SIZE;
  int pixel_col = col * PIXEL_SIZE;

  for (int drow = 0; drow < PIXEL_SIZE; drow++) {
    for (int dcol = 0; dcol < PIXEL_SIZE; dcol++) {
      paint_pixel(pixel_row + drow, pixel_col + dcol, color);
    }
  }
}
