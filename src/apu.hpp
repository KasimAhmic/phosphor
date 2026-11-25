#pragma once

#include <cstdint>

class APU {
public:
  APU();
  ~APU();

  [[nodiscard]] std::uint8_t read_register(std::uint16_t addr);
};
