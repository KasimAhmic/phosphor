#include "nes_bus.hpp"

NESBus::NESBus(PPU& ppu, APU& apu, Cartridge& cartridge, Controller& controller1, Controller& controller2)
    : ppu_{ppu},
      apu_{apu},
      cartridge_{cartridge},
      controller1_{controller1},
      controller2_{controller2} {}

NESBus::~NESBus() = default;

std::uint8_t NESBus::read(std::uint16_t addr) {
  if (addr < 0x2000) {
    return this->ram_[addr & 0x07FF];
  }

  if (addr < 0x4000) {
    return this->ppu_.read_register(addr & 0x0007);
  }

  if (addr < 0x4018) {
    switch (addr) {
    case 0x4015:
      return this->apu_.read_register(0x15);

    case 0x4016:
      return this->controller1_.read();

    case 0x4017:
      return this->controller2_.read();

    default:
      return 0; // TODO: Open bus
    }
  }

  if (addr < 0x4020) {
    return 0; // TODO: Open bus
  }

  return this->cartridge_.cpu_read(addr);
}

void NESBus::write(std::uint16_t addr, std::uint8_t value) {
  if (addr < 0x2000) {
    this->ram_[addr & 0x07FF] = value;
  }
}
