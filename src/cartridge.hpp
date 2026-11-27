#pragma once

#include <cstdint>
#include <span>

class Cartridge {
public:
  explicit Cartridge();
  ~Cartridge();

  void load(const std::span<std::uint8_t>& data);

  [[nodiscard]] std::uint8_t cpu_read(std::uint16_t addr);
  void cpu_write(std::uint16_t addr, std::uint8_t value);

  [[nodiscard]] std::uint8_t ppu_read(std::uint16_t addr);
  void ppu_write(std::uint16_t addr, std::uint8_t value);

private:
  std::span<std::uint8_t> data_;
};
