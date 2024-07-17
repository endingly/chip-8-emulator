#pragma once

#include "operand.hpp"
// initialize graphics
// glutInit(&argc, argv);
// glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
// glutInitWindowSize(chip8System->SCREEN_HEIGHT * SCREEN_PIXELS, chip8System->SCREEN_WIDTH * SCREEN_PIXELS);
// glutInitWindowPosition(0, 0);
// glutCreateWindow("CHIP-8 Emulator");

namespace chip_8 {

class Monitor {
  using ScreenColor = unsigned char;

 private:
  constexpr static int    PIXEL_SIZE    = 5;
  constexpr static int8_t BLACK         = 0x00;
  constexpr static int8_t WHITE         = 0xFF;
  constexpr static int    SCREEN_HEIGHT = (chip_8::Chip8System::SCREEN_HEIGHT * PIXEL_SIZE);
  constexpr static int    SCREEN_WIDTH  = (chip_8::Chip8System::SCREEN_WIDTH * PIXEL_SIZE);
  ScreenColor             screen[SCREEN_HEIGHT][SCREEN_WIDTH][3];

 public:
  Monitor()  = default;
  ~Monitor() = default;
  /// @brief draws the screen with the current state of the emulator.
  void draw_screen();
  /// @brief Reshape the window to the given width and height.
  /// @param width width of the window.
  /// @param height height of the window.
  void reshape_window(int width, int height);

 private:
  /// @brief Draws a pixel at the given row and column with the given color with RGB format.
  /// @param row row index of the pixel to be drawn.
  /// @param col column index of the pixel to be drawn.
  /// @param color color of the pixel to be drawn.
  /// @note The color is in RGB format. But chip-8 system only have one color depth, so the R, G, and B values are the
  /// same.
  inline void paint_pixel(int row, int col, ScreenColor color);
  /// @brief draws a cell at the given row and column with the given color.
  /// @note A cell is a 5x5 pixel square.
  /// @param row row index of the cell to be drawn.
  /// @param col column index of the cell to be drawn.
  /// @param color color of the cell to be drawn.
  void paint_cell(int row, int col, ScreenColor color);
};

};  // namespace chip_8
