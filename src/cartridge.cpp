#include "cartridge.hpp"

Cartridge::Cartridge() = default;

Cartridge::~Cartridge() = default;

void Cartridge::load(const std::span<std::uint8_t>& data) {}

std::uint8_t Cartridge::cpu_read(const std::uint16_t addr) { return 0; }

void Cartridge::cpu_write(const std::uint16_t addr, const std::uint8_t value) {}

std::uint8_t Cartridge::ppu_read(const std::uint16_t addr) { return 0; }

void Cartridge::ppu_write(const std::uint16_t addr, const std::uint8_t value) {}
