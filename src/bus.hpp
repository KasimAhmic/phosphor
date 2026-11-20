#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

class Bus {
public:
  std::uint8_t read(std::uint16_t address) const;

  void write(std::uint16_t address, std::uint8_t value);

private:
  std::vector<std::uint8_t> ram = std::vector<std::uint8_t>(2048);
  std::vector<std::uint8_t> rom;
};
