#pragma once

#include <algorithm>
#include <array>

#include "addressing_mode.hpp"
#include "instruction.hpp"

struct OpCode {
  Instruction instruction{Instruction::Unimplemented};
  AddressingMode mode;
};

constexpr auto opcodes = [] {
  std::array<OpCode, 256> table{};

  table[0x69] = {Instruction::ADC, AddressingMode::Immediate};
  table[0x65] = {Instruction::ADC, AddressingMode::ZeroPage};
  table[0x75] = {Instruction::ADC, AddressingMode::ZeroPageX};
  table[0x6D] = {Instruction::ADC, AddressingMode::Absolute};
  table[0x7D] = {Instruction::ADC, AddressingMode::AbsoluteX};
  table[0x79] = {Instruction::ADC, AddressingMode::AbsoluteY};
  table[0x61] = {Instruction::ADC, AddressingMode::IndexedIndirect};
  table[0x71] = {Instruction::ADC, AddressingMode::IndirectIndexed};

  table[0x29] = {Instruction::AND, AddressingMode::Immediate};
  table[0x25] = {Instruction::AND, AddressingMode::ZeroPage};
  table[0x35] = {Instruction::AND, AddressingMode::ZeroPageX};
  table[0x2D] = {Instruction::AND, AddressingMode::Absolute};
  table[0x3D] = {Instruction::AND, AddressingMode::AbsoluteX};
  table[0x39] = {Instruction::AND, AddressingMode::AbsoluteY};
  table[0x21] = {Instruction::AND, AddressingMode::IndexedIndirect};
  table[0x31] = {Instruction::AND, AddressingMode::IndirectIndexed};

  table[0x0A] = {Instruction::ASL, AddressingMode::Accumulator};
  table[0x06] = {Instruction::ASL, AddressingMode::ZeroPage};
  table[0x16] = {Instruction::ASL, AddressingMode::ZeroPageX};
  table[0x0E] = {Instruction::ASL, AddressingMode::Absolute};
  table[0x1E] = {Instruction::ASL, AddressingMode::AbsoluteX};

  table[0x90] = {Instruction::BCC, AddressingMode::Relative};
  table[0xB0] = {Instruction::BCS, AddressingMode::Relative};
  table[0xF0] = {Instruction::BEQ, AddressingMode::Relative};
  table[0x24] = {Instruction::BIT, AddressingMode::ZeroPage};
  table[0x2C] = {Instruction::BIT, AddressingMode::Absolute};
  table[0x30] = {Instruction::BMI, AddressingMode::Relative};
  table[0xD0] = {Instruction::BNE, AddressingMode::Relative};
  table[0x10] = {Instruction::BPL, AddressingMode::Relative};
  table[0x00] = {Instruction::BRK, AddressingMode::Implied};
  table[0x50] = {Instruction::BVC, AddressingMode::Relative};
  table[0x70] = {Instruction::BVS, AddressingMode::Relative};

  table[0x18] = {Instruction::CLC, AddressingMode::Implied};
  table[0xD8] = {Instruction::CLD, AddressingMode::Implied};
  table[0x58] = {Instruction::CLI, AddressingMode::Implied};
  table[0xB8] = {Instruction::CLV, AddressingMode::Implied};

  table[0xC9] = {Instruction::CMP, AddressingMode::Immediate};
  table[0xC5] = {Instruction::CMP, AddressingMode::ZeroPage};
  table[0xD5] = {Instruction::CMP, AddressingMode::ZeroPageX};
  table[0xCD] = {Instruction::CMP, AddressingMode::Absolute};
  table[0xDD] = {Instruction::CMP, AddressingMode::AbsoluteX};
  table[0xD9] = {Instruction::CMP, AddressingMode::AbsoluteY};
  table[0xC1] = {Instruction::CMP, AddressingMode::IndexedIndirect};
  table[0xD1] = {Instruction::CMP, AddressingMode::IndirectIndexed};

  table[0xE0] = {Instruction::CPX, AddressingMode::Immediate};
  table[0xE4] = {Instruction::CPX, AddressingMode::ZeroPage};
  table[0xEC] = {Instruction::CPX, AddressingMode::Absolute};

  table[0xC0] = {Instruction::CPY, AddressingMode::Immediate};
  table[0xC4] = {Instruction::CPY, AddressingMode::ZeroPage};
  table[0xCC] = {Instruction::CPY, AddressingMode::Absolute};

  table[0xC6] = {Instruction::DEC, AddressingMode::ZeroPage};
  table[0xD6] = {Instruction::DEC, AddressingMode::ZeroPageX};
  table[0xCE] = {Instruction::DEC, AddressingMode::Absolute};
  table[0xDE] = {Instruction::DEC, AddressingMode::AbsoluteX};

  table[0xCA] = {Instruction::DEX, AddressingMode::Implied};
  table[0x88] = {Instruction::DEY, AddressingMode::Implied};

  table[0x49] = {Instruction::EOR, AddressingMode::Immediate};
  table[0x45] = {Instruction::EOR, AddressingMode::ZeroPage};
  table[0x55] = {Instruction::EOR, AddressingMode::ZeroPageX};
  table[0x4D] = {Instruction::EOR, AddressingMode::Absolute};
  table[0x5D] = {Instruction::EOR, AddressingMode::AbsoluteX};
  table[0x59] = {Instruction::EOR, AddressingMode::AbsoluteY};
  table[0x41] = {Instruction::EOR, AddressingMode::IndexedIndirect};
  table[0x51] = {Instruction::EOR, AddressingMode::IndirectIndexed};

  table[0xE6] = {Instruction::INC, AddressingMode::ZeroPage};
  table[0xF6] = {Instruction::INC, AddressingMode::ZeroPageX};
  table[0xEE] = {Instruction::INC, AddressingMode::Absolute};
  table[0xFE] = {Instruction::INC, AddressingMode::AbsoluteX};

  table[0xE8] = {Instruction::INX, AddressingMode::Implied};
  table[0xC8] = {Instruction::INY, AddressingMode::Implied};

  table[0x4C] = {Instruction::JMP, AddressingMode::Absolute};
  table[0x6C] = {Instruction::JMP, AddressingMode::Indirect};

  table[0x20] = {Instruction::JSR, AddressingMode::Absolute};

  table[0xA9] = {Instruction::LDA, AddressingMode::Immediate};
  table[0xA5] = {Instruction::LDA, AddressingMode::ZeroPage};
  table[0xB5] = {Instruction::LDA, AddressingMode::ZeroPageX};
  table[0xAD] = {Instruction::LDA, AddressingMode::Absolute};
  table[0xBD] = {Instruction::LDA, AddressingMode::AbsoluteX};
  table[0xB9] = {Instruction::LDA, AddressingMode::AbsoluteY};
  table[0xA1] = {Instruction::LDA, AddressingMode::IndexedIndirect};
  table[0xB1] = {Instruction::LDA, AddressingMode::IndirectIndexed};

  table[0xA2] = {Instruction::LDX, AddressingMode::Immediate};
  table[0xA6] = {Instruction::LDX, AddressingMode::ZeroPage};
  table[0xB6] = {Instruction::LDX, AddressingMode::ZeroPageY};
  table[0xAE] = {Instruction::LDX, AddressingMode::Absolute};
  table[0xBE] = {Instruction::LDX, AddressingMode::AbsoluteY};

  table[0xA0] = {Instruction::LDY, AddressingMode::Immediate};
  table[0xA4] = {Instruction::LDY, AddressingMode::ZeroPage};
  table[0xB4] = {Instruction::LDY, AddressingMode::ZeroPageX};
  table[0xAC] = {Instruction::LDY, AddressingMode::Absolute};
  table[0xBC] = {Instruction::LDY, AddressingMode::AbsoluteX};

  table[0x4A] = {Instruction::LSR, AddressingMode::Accumulator};
  table[0x46] = {Instruction::LSR, AddressingMode::ZeroPage};
  table[0x56] = {Instruction::LSR, AddressingMode::ZeroPageX};
  table[0x4E] = {Instruction::LSR, AddressingMode::Absolute};
  table[0x5E] = {Instruction::LSR, AddressingMode::AbsoluteX};

  table[0xEA] = {Instruction::NOP, AddressingMode::Implied};

  table[0x09] = {Instruction::ORA, AddressingMode::Immediate};
  table[0x05] = {Instruction::ORA, AddressingMode::ZeroPage};
  table[0x15] = {Instruction::ORA, AddressingMode::ZeroPageX};
  table[0x0D] = {Instruction::ORA, AddressingMode::Absolute};
  table[0x1D] = {Instruction::ORA, AddressingMode::AbsoluteX};
  table[0x19] = {Instruction::ORA, AddressingMode::AbsoluteY};
  table[0x01] = {Instruction::ORA, AddressingMode::IndexedIndirect};
  table[0x11] = {Instruction::ORA, AddressingMode::IndirectIndexed};

  table[0x48] = {Instruction::PHA, AddressingMode::Implied};
  table[0x08] = {Instruction::PHP, AddressingMode::Implied};

  table[0x68] = {Instruction::PLA, AddressingMode::Implied};
  table[0x28] = {Instruction::PLP, AddressingMode::Implied};

  table[0x2A] = {Instruction::ROL, AddressingMode::Accumulator};
  table[0x26] = {Instruction::ROL, AddressingMode::ZeroPage};
  table[0x36] = {Instruction::ROL, AddressingMode::ZeroPageX};
  table[0x2E] = {Instruction::ROL, AddressingMode::Absolute};
  table[0x3E] = {Instruction::ROL, AddressingMode::AbsoluteX};

  table[0x6A] = {Instruction::ROR, AddressingMode::Accumulator};
  table[0x66] = {Instruction::ROR, AddressingMode::ZeroPage};
  table[0x76] = {Instruction::ROR, AddressingMode::ZeroPageX};
  table[0x6E] = {Instruction::ROR, AddressingMode::Absolute};
  table[0x7E] = {Instruction::ROR, AddressingMode::AbsoluteX};

  table[0x40] = {Instruction::RTI, AddressingMode::Implied};
  table[0x60] = {Instruction::RTS, AddressingMode::Implied};

  table[0xE9] = {Instruction::SBC, AddressingMode::Immediate};
  table[0xE5] = {Instruction::SBC, AddressingMode::ZeroPage};
  table[0xF5] = {Instruction::SBC, AddressingMode::ZeroPageX};
  table[0xED] = {Instruction::SBC, AddressingMode::Absolute};
  table[0xFD] = {Instruction::SBC, AddressingMode::AbsoluteX};
  table[0xF9] = {Instruction::SBC, AddressingMode::AbsoluteY};
  table[0xE1] = {Instruction::SBC, AddressingMode::IndexedIndirect};
  table[0xF1] = {Instruction::SBC, AddressingMode::IndirectIndexed};

  table[0x38] = {Instruction::SEC, AddressingMode::Implied};
  table[0xF8] = {Instruction::SED, AddressingMode::Implied};
  table[0x78] = {Instruction::SEI, AddressingMode::Implied};

  table[0x85] = {Instruction::STA, AddressingMode::ZeroPage};
  table[0x95] = {Instruction::STA, AddressingMode::ZeroPageX};
  table[0x8D] = {Instruction::STA, AddressingMode::Absolute};
  table[0x9D] = {Instruction::STA, AddressingMode::AbsoluteX};
  table[0x99] = {Instruction::STA, AddressingMode::AbsoluteY};
  table[0x81] = {Instruction::STA, AddressingMode::IndexedIndirect};
  table[0x91] = {Instruction::STA, AddressingMode::IndirectIndexed};

  table[0x86] = {Instruction::STX, AddressingMode::ZeroPage};
  table[0x96] = {Instruction::STX, AddressingMode::ZeroPageY};
  table[0x8E] = {Instruction::STX, AddressingMode::Absolute};

  table[0x84] = {Instruction::STY, AddressingMode::ZeroPage};
  table[0x94] = {Instruction::STY, AddressingMode::ZeroPageX};
  table[0x8C] = {Instruction::STY, AddressingMode::Absolute};

  table[0xAA] = {Instruction::TAX, AddressingMode::Implied};
  table[0xA8] = {Instruction::TAY, AddressingMode::Implied};
  table[0xBA] = {Instruction::TSX, AddressingMode::Implied};
  table[0x8A] = {Instruction::TXA, AddressingMode::Implied};
  table[0x9A] = {Instruction::TXS, AddressingMode::Implied};
  table[0x98] = {Instruction::TYA, AddressingMode::Implied};

  return table;
}();

static_assert(std::ranges::count_if(opcodes,
                                    [](const OpCode& op) { return op.instruction != Instruction::Unimplemented; }) ==
                  151,
              "Expected 151 populated opcode entries");
