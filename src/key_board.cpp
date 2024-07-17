#include "key_board.hpp"

const std::map<unsigned char, int32_t> chip_8::KeyBoard::key_map_ = {
    {'1', 0x1}, {'2', 0x2}, {'3', 0x3}, {'4', 0xc}, {'q', 0x4}, {'w', 0x5}, {'e', 0x6}, {'r', 0xd},
    {'a', 0x7}, {'s', 0x8}, {'d', 0x9}, {'f', 0xe}, {'z', 0xa}, {'x', 0x0}, {'c', 0xb}, {'v', 0xf}};

void chip_8::KeyBoard::key_pressed(unsigned char key) { auto index = key_map_.at(key); }

void chip_8::KeyBoard::key_released(unsigned char key) { auto index = key_map_.at(key); }
