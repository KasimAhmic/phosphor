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
  PPU _ppu;
  APU _apu;
  Cartridge _cartridge;
  Controller _controller1;
  Controller _controller2;
  NESBus _bus;
  CPU _cpu;
};
