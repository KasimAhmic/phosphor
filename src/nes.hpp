#pragma once

#include <filesystem>
#include <span>

#include "apu.hpp"
#include "cpu.hpp"
#include "ppu.hpp"

class NES {
public:
  NES();
  ~NES();

  std::vector<std::uint8_t> load_rom(const std::filesystem::path& path);
  void reset();
  void test();

private:
  CPU _cpu;
  PPU _ppu;
  APU _apu;
};
