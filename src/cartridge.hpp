#pragma once

#include <cstdint>

class Cartridge {
public:
  explicit Cartridge();
  ~Cartridge();

  [[nodiscard]] std::uint8_t cpu_read(std::uint16_t addr);
  void cpu_write(std::uint16_t addr, std::uint8_t value);

  [[nodiscard]] std::uint8_t ppu_read(std::uint16_t addr);
  void ppu_write(std::uint16_t addr, std::uint8_t value);
};
