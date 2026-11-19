#pragma once

#include <span>

#include "apu.hpp"
#include "cpu.hpp"
#include "ppu.hpp"

class NES {
public:
  NES();
  ~NES();

  void load_rom(const std::span<const std::byte> rom);
  void reset();

private:
  CPU _cpu;
  PPU _ppu;
  APU _apu;
};
