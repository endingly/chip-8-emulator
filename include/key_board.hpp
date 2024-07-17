#pragma once
#include <cstdint>
#include <map>

namespace chip_8 {
class KeyBoard {
 private:
  const static std::map<unsigned char, int32_t> key_map_;  // map of key to its index in the key_state_ array

 public:
  KeyBoard()  = default;
  ~KeyBoard() = default;
  void key_pressed(unsigned char key);
  void key_released(unsigned char key);
};
}  // namespace chip_8
