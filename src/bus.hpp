#pragma once

#include <cstdint>

class Bus {
public:
  virtual ~Bus() = default;

  virtual std::uint8_t read(std::uint16_t addr)              = 0;
  virtual void write(std::uint16_t addr, std::uint8_t value) = 0;
};
