#include <stdexcept>

#include <format>
#include <string>
#include "cpu.hpp"
#include "opcode.hpp"

CPU::CPU(std::array<std::uint8_t, 65536> mem) : _registers(), _cycle_count(0), _memory(mem) {}

CPU::~CPU() {}

void CPU::reset() {
  this->_registers.pc = 0xC000;
  this->_registers.a  = 0x00;
  this->_registers.x  = 0x00;
  this->_registers.y  = 0x00;
  this->_registers.p  = 0x24;
  this->_registers.sp = 0xFD;

  this->_cycle_count = 7;
}

std::uint8_t CPU::read(std::uint16_t addr) {
  const std::uint8_t value = _memory[addr];

  this->tick();

  return value;
}

void CPU::write(std::uint16_t addr, std::uint8_t value) {
  _memory[addr] = value;

  this->tick();
}

void CPU::tick() {
  // TODO: For cycle accurate emulation, will do later
}

std::int8_t CPU::step() {
  const auto opcode = this->read(this->_registers.pc++);

  switch (opcode) {

  case OpCode::ADC::Immediate: {
    break;
  }

  case 0x65: {
    break;
  }

  case 0x75: {
    break;
  }

  case 0x6D: {
    break;
  }

  case 0x7D: {
    break;
  }

  case 0x79: {
    break;
  }

  case 0x61: {
    break;
  }

  case 0x71: {
    break;
  }

  case 0x29: {
    break;
  }

  case 0x25: {
    break;
  }

  case 0x35: {
    break;
  }

  case 0x2D: {
    break;
  }

  case 0x3D: {
    break;
  }

  case 0x39: {
    break;
  }

  case 0x21: {
    break;
  }

  case 0x31: {
    break;
  }

  case 0x0A: {
    break;
  }

  case 0x06: {
    break;
  }

  case 0x16: {
    break;
  }

  case 0x0E: {
    break;
  }

  case 0x1E: {
    break;
  }

  case 0x90: {
    break;
  }

  case 0xB0: {
    break;
  }

  case 0xF0: {
    break;
  }

  case 0x24: {
    break;
  }

  case 0x2C: {
    break;
  }

  case 0x30: {
    break;
  }

  case 0xD0: {
    break;
  }

  case 0x10: {
    break;
  }

  case 0x00: {
    break;
  }

  case 0x50: {
    break;
  }

  case 0x70: {
    break;
  }

  case 0x18: {
    break;
  }

  case 0xD8: {
    break;
  }

  case 0x58: {
    break;
  }

  case 0xB8: {
    break;
  }

  case 0xC9: {
    break;
  }

  case 0xC5: {
    break;
  }

  case 0xD5: {
    break;
  }

  case 0xCD: {
    break;
  }

  case 0xDD: {
    break;
  }

  case 0xD9: {
    break;
  }

  case 0xC1: {
    break;
  }

  case 0xD1: {
    break;
  }

  case 0xE0: {
    break;
  }

  case 0xE4: {
    break;
  }

  case 0xEC: {
    break;
  }

  case 0xC0: {
    break;
  }

  case 0xC4: {
    break;
  }

  case 0xCC: {
    break;
  }

  case 0xC6: {
    break;
  }

  case 0xD6: {
    break;
  }

  case 0xCE: {
    break;
  }

  case 0xDE: {
    break;
  }

  case 0xCA: {
    break;
  }

  case 0x88: {
    break;
  }

  case 0x49: {
    break;
  }

  case 0x45: {
    break;
  }

  case 0x55: {
    break;
  }

  case 0x4D: {
    break;
  }

  case 0x5D: {
    break;
  }

  case 0x59: {
    break;
  }

  case 0x41: {
    break;
  }

  case 0x51: {
    break;
  }

  case 0xE6: {
    break;
  }

  case 0xF6: {
    break;
  }

  case 0xEE: {
    break;
  }

  case 0xFE: {
    break;
  }

  case 0xE8: {
    break;
  }

  case 0xC8: {
    break;
  }

  case 0x4C: {
    const auto low  = this->read(_registers.pc++);
    const auto high = this->read(_registers.pc++);

    this->_registers.pc = static_cast<std::uint16_t>(low | (high << 8));
    this->_cycle_count += 3;

    return 3;
  }

  case 0x6C: {
    break;
  }

  case 0x20: {
    const auto low = this->read(_registers.pc++);
    (void)this->read(0x0100 | this->_registers.sp);
    const auto return_addr = this->_registers.pc;

    this->_memory[0x0100 | this->_registers.sp--] = static_cast<std::uint8_t>(return_addr >> 8);
    this->_memory[0x0100 | this->_registers.sp--] = static_cast<std::uint8_t>(return_addr & 0xFF);

    const auto high = this->read(_registers.pc++);

    this->_registers.pc = static_cast<std::uint16_t>(low | (high << 8));

    this->_cycle_count += 6;

    return 6;
  }

  case 0xA9: {
    break;
  }

  case 0xA5: {
    break;
  }

  case 0xB5: {
    break;
  }

  case 0xAD: {
    break;
  }

  case 0xBD: {
    break;
  }

  case 0xB9: {
    break;
  }

  case 0xA1: {
    break;
  }

  case 0xB1: {
    break;
  }

  case 0xA2: {
    this->_registers.x = this->read(_registers.pc++);

    if (this->_registers.x == 0) {
      this->_registers.p |= 0x02;
    } else {
      this->_registers.p &= ~0x02;
    }

    this->_cycle_count += 2;

    return 2;
  }

  case 0xA6: {
    break;
  }

  case 0xB6: {
    break;
  }

  case 0xAE: {
    break;
  }

  case 0xBE: {
    break;
  }

  case 0xA0: {
    break;
  }

  case 0xA4: {
    break;
  }

  case 0xB4: {
    break;
  }

  case 0xAC: {
    break;
  }

  case 0xBC: {
    break;
  }

  case 0x4A: {
    break;
  }

  case 0x46: {
    break;
  }

  case 0x56: {
    break;
  }

  case 0x4E: {
    break;
  }

  case 0x5E: {
    break;
  }

  case 0xEA: {
    break;
  }

  case 0x09: {
    break;
  }

  case 0x05: {
    break;
  }

  case 0x15: {
    break;
  }

  case 0x0D: {
    break;
  }

  case 0x1D: {
    break;
  }

  case 0x19: {
    break;
  }

  case 0x01: {
    break;
  }

  case 0x11: {
    break;
  }

  case 0x48: {
    break;
  }

  case 0x08: {
    break;
  }

  case 0x68: {
    break;
  }

  case 0x28: {
    break;
  }

  case 0x2A: {
    break;
  }

  case 0x26: {
    break;
  }

  case 0x36: {
    break;
  }

  case 0x2E: {
    break;
  }

  case 0x3E: {
    break;
  }

  case 0x6A: {
    break;
  }

  case 0x66: {
    break;
  }

  case 0x76: {
    break;
  }

  case 0x6E: {
    break;
  }

  case 0x7E: {
    break;
  }

  case 0x40: {
    break;
  }

  case 0x60: {
    break;
  }

  case 0xE9: {
    break;
  }

  case 0xE5: {
    break;
  }

  case 0xF5: {
    break;
  }

  case 0xED: {
    break;
  }

  case 0xFD: {
    break;
  }

  case 0xF9: {
    break;
  }

  case 0xE1: {
    break;
  }

  case 0xF1: {
    break;
  }

  case 0x38: {
    break;
  }

  case 0xF8: {
    break;
  }

  case 0x78: {
    break;
  }

  case 0x85: {
    break;
  }

  case 0x95: {
    break;
  }

  case 0x8D: {
    break;
  }

  case 0x9D: {
    break;
  }

  case 0x99: {
    break;
  }

  case 0x81: {
    break;
  }

  case 0x91: {
    break;
  }

  case 0x86: {
    const auto addr     = this->_memory[this->_registers.pc++];
    this->_memory[addr] = this->_registers.x;
    this->_cycle_count += 3;

    return 3;
  }

  case 0x96: {
    break;
  }

  case 0x8E: {
    break;
  }

  case 0x84: {
    break;
  }

  case 0x94: {
    break;
  }

  case 0x8C: {
    break;
  }

  case 0xAA: {
    break;
  }

  case 0xA8: {
    break;
  }

  case 0xBA: {
    break;
  }

  case 0x8A: {
    break;
  }

  case 0x9A: {
    break;
  }

  case 0x98: {
    break;
  }
  }

  return -1;
}
