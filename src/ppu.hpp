#pragma once

#include <cstdint>

class PPU {
public:
  PPU();
  ~PPU();

  [[nodiscard]] std::uint8_t read_register(std::uint16_t addr);
};
