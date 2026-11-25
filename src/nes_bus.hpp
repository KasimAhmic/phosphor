#pragma once

#include <array>

#include "apu.hpp"
#include "bus.hpp"
#include "cartridge.hpp"
#include "controller.hpp"
#include "ppu.hpp"

class NESBus final : public Bus {
public:
  explicit NESBus(PPU& ppu, APU& apu, Cartridge& cartridge, Controller& controller1, Controller& controller2);
  ~NESBus() override;

  std::uint8_t read(std::uint16_t addr) override;
  void write(std::uint16_t addr, std::uint8_t value) override;

private:
  PPU& _ppu;
  APU& _apu;
  Cartridge& _cartridge;
  Controller& _controller1;
  Controller& _controller2;

  std::array<std::uint8_t, 2048> _ram{};
};
