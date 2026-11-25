#pragma once

#include <array>
#include <cstdint>

#include "bus.hpp"

class TestBus final : public Bus {
public:
  explicit TestBus();
  ~TestBus() override;

  std::uint8_t read(std::uint16_t addr) override;
  void write(std::uint16_t addr, std::uint8_t value) override;

private:
  std::array<std::uint8_t, 0x10000> _memory;
};
