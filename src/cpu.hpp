#pragma once

#include <cstdint>

class CPU {
public:
  CPU();
  ~CPU();

  std::uint8_t step();
  void set_flag();
};
