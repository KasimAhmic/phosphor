#include "nes_bus.hpp"

NESBus::NESBus(PPU& ppu, APU& apu, Cartridge& cartridge, Controller& controller1, Controller& controller2)
    : _ppu{ppu},
      _apu{apu},
      _cartridge{cartridge},
      _controller1{controller1},
      _controller2{controller2} {}

NESBus::~NESBus() = default;

std::uint8_t NESBus::read(std::uint16_t addr) { return 0; }

void NESBus::write(std::uint16_t addr, std::uint8_t value) {}
