#include "nes.hpp"

#include <array>
#include <fstream>

NES::NES() : _cpu(std::array<std::uint8_t, 65536>{}), _ppu(), _apu() {};

NES::~NES() = default;

void NES::reset() {}
