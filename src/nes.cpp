#include "nes.hpp"

NES::NES() : _cpu(), _ppu(), _apu() {};

NES::~NES() {};

void NES::load_rom(const std::span<const std::byte> rom) {
  // Implement ROM loading logic here
}

void NES::reset() {
  // Implement reset logic here
}
