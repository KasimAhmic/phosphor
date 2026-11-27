#pragma once

#include "apu.hpp"
#include "cartridge.hpp"
#include "controller.hpp"
#include "cpu.hpp"
#include "nes_bus.hpp"
#include "ppu.hpp"

class NES {
public:
  NES();
  ~NES();

  NES(const NES&) = delete;
  NES(NES&&)      = delete;

  NES& operator=(const NES&) = delete;
  NES& operator=(NES&&)      = delete;

private:
  PPU ppu_;
  APU apu_;
  Cartridge cartridge_;
  Controller controller1_;
  Controller controller2_;
  NESBus bus_;
  CPU cpu_;
};
