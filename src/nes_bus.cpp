#include "nes_bus.hpp"

NESBus::NESBus(PPU& ppu, APU& apu, Cartridge& cartridge, Controller& controller1, Controller& controller2)
    : _ppu{ppu},
      _apu{apu},
      _cartridge{cartridge},
      _controller1{controller1},
      _controller2{controller2} {}

NESBus::~NESBus() = default;

std::uint8_t NESBus::read(std::uint16_t addr) {
  if (addr < 0x2000) {
    return this->_ram[addr & 0x07FF];
  }

  if (addr < 0x4000) {
    return this->_ppu.read_register(addr & 0x0007);
  }

  if (addr < 0x4018) {
    switch (addr) {
    case 0x4015:
      return this->_apu.read_register(0x15);

    case 0x4016:
      return this->_controller1.read();

    case 0x4017:
      return this->_controller2.read();

    default:
      return 0; // TODO: Open bus
    }
  }

  if (addr < 0x4020) {
    return 0; // TODO: Open bus
  }

  return this->_cartridge.cpu_read(addr);
}

void NESBus::write(std::uint16_t addr, std::uint8_t value) {
  if (addr < 0x2000) {
    this->_ram[addr & 0x07FF] = value;
  }
}
