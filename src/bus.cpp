#include "bus.hpp"

std::uint8_t Bus::read(std::uint16_t address) const {
  // Internal RAM (2 KB, mirrored)
  if (address < 0x2000) {
    return ram[address & 0x07FF];
  }

  // Mapper 0 PRG-ROM
  if (address >= 0x8000) {
    const auto offset = address - 0x8000;
    return rom[offset % rom.size()];
  }

  // PPU, APU, cartridge RAM, etc.
  throw std::runtime_error("Unimplemented bus address");
}

void Bus::write(std::uint16_t address, std::uint8_t value) {
  if (address < 0x2000) {
    ram[address & 0x07FF] = value;
    return;
  }

  // TODO: PPU/APU registers, cartridge memory, etc.
}
