#pragma once

#include <cstdint>

#include "addressing_mode.hpp"
#include "instruction.hpp"

namespace OpCode {
  struct Definition {
    std::uint8_t code{};
    Instruction instruction{Instruction::Unimplemented};
    AddressingMode mode;

    constexpr operator std::uint8_t() const { return code; }
    constexpr operator Instruction() const { return instruction; }
    constexpr operator AddressingMode() const { return mode; }
  };

  namespace ADC {
    constexpr Definition Immediate       = {0x69, Instruction::ADC, AddressingMode::Immediate};
    constexpr Definition ZeroPage        = {0x65, Instruction::ADC, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX       = {0x75, Instruction::ADC, AddressingMode::ZeroPageX};
    constexpr Definition Absolute        = {0x6D, Instruction::ADC, AddressingMode::Absolute};
    constexpr Definition AbsoluteX       = {0x7D, Instruction::ADC, AddressingMode::AbsoluteX};
    constexpr Definition AbsoluteY       = {0x79, Instruction::ADC, AddressingMode::AbsoluteY};
    constexpr Definition IndexedIndirect = {0x61, Instruction::ADC, AddressingMode::IndexedIndirect};
    constexpr Definition IndirectIndexed = {0x71, Instruction::ADC, AddressingMode::IndirectIndexed};
  } // namespace ADC

  namespace AND {
    constexpr Definition Immediate       = {0x29, Instruction::AND, AddressingMode::Immediate};
    constexpr Definition ZeroPage        = {0x25, Instruction::AND, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX       = {0x35, Instruction::AND, AddressingMode::ZeroPageX};
    constexpr Definition Absolute        = {0x2D, Instruction::AND, AddressingMode::Absolute};
    constexpr Definition AbsoluteX       = {0x3D, Instruction::AND, AddressingMode::AbsoluteX};
    constexpr Definition AbsoluteY       = {0x39, Instruction::AND, AddressingMode::AbsoluteY};
    constexpr Definition IndexedIndirect = {0x21, Instruction::AND, AddressingMode::IndexedIndirect};
    constexpr Definition IndirectIndexed = {0x31, Instruction::AND, AddressingMode::IndirectIndexed};

  } // namespace AND

  namespace ASL {
    constexpr Definition Accumulator = {0x0A, Instruction::ASL, AddressingMode::Accumulator};
    constexpr Definition ZeroPage    = {0x06, Instruction::ASL, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX   = {0x16, Instruction::ASL, AddressingMode::ZeroPageX};
    constexpr Definition Absolute    = {0x0E, Instruction::ASL, AddressingMode::Absolute};
    constexpr Definition AbsoluteX   = {0x1E, Instruction::ASL, AddressingMode::AbsoluteX};
  } // namespace ASL

  namespace BCC {
    constexpr Definition Relative = {0x90, Instruction::BCC, AddressingMode::Relative};
  }

  namespace BCS {
    constexpr Definition Relative = {0xB0, Instruction::BCS, AddressingMode::Relative};
  }

  namespace BEQ {
    constexpr Definition Relative = {0xF0, Instruction::BEQ, AddressingMode::Relative};
  }

  namespace BIT {
    constexpr Definition ZeroPage = {0x24, Instruction::BIT, AddressingMode::ZeroPage};
    constexpr Definition Absolute = {0x2C, Instruction::BIT, AddressingMode::Absolute};
  } // namespace BIT

  namespace BMI {
    constexpr Definition Relative = {0x30, Instruction::BMI, AddressingMode::Relative};
  }

  namespace BNE {
    constexpr Definition Relative = {0xD0, Instruction::BNE, AddressingMode::Relative};
  }

  namespace BPL {
    constexpr Definition Relative = {0x10, Instruction::BPL, AddressingMode::Relative};
  }

  namespace BRK {
    constexpr Definition Implied = {0x00, Instruction::BRK, AddressingMode::Implied};
  }

  namespace BVC {
    constexpr Definition Relative = {0x50, Instruction::BVC, AddressingMode::Relative};
  }

  namespace BVS {
    constexpr Definition Relative = {0x70, Instruction::BVS, AddressingMode::Relative};
  }

  namespace CLC {
    constexpr Definition Implied = {0x18, Instruction::CLC, AddressingMode::Implied};
  }

  namespace CLD {
    constexpr Definition Implied = {0xD8, Instruction::CLD, AddressingMode::Implied};
  }

  namespace CLI {
    constexpr Definition Implied = {0x58, Instruction::CLI, AddressingMode::Implied};
  }

  namespace CLV {
    constexpr Definition Implied = {0xB8, Instruction::CLV, AddressingMode::Implied};
  }

  namespace CMP {
    constexpr Definition Immediate = {0xC9, Instruction::CMP, AddressingMode::Immediate};

    constexpr Definition ZeroPage        = {0xC5, Instruction::CMP, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX       = {0xD5, Instruction::CMP, AddressingMode::ZeroPageX};
    constexpr Definition Absolute        = {0xCD, Instruction::CMP, AddressingMode::Absolute};
    constexpr Definition AbsoluteX       = {0xDD, Instruction::CMP, AddressingMode::AbsoluteX};
    constexpr Definition AbsoluteY       = {0xD9, Instruction::CMP, AddressingMode::AbsoluteY};
    constexpr Definition IndexedIndirect = {0xC1, Instruction::CMP, AddressingMode::IndexedIndirect};
    constexpr Definition IndirectIndexed = {0xD1, Instruction::CMP, AddressingMode::IndirectIndexed};
  } // namespace CMP

  namespace CPX {
    constexpr Definition Immediate = {0xE0, Instruction::CPX, AddressingMode::Immediate};
    constexpr Definition ZeroPage  = {0xE4, Instruction::CPX, AddressingMode::ZeroPage};
    constexpr Definition Absolute  = {0xEC, Instruction::CPX, AddressingMode::Absolute};
  } // namespace CPX

  namespace CPY {
    constexpr Definition Immediate = {0xC0, Instruction::CPY, AddressingMode::Immediate};
    constexpr Definition ZeroPage  = {0xC4, Instruction::CPY, AddressingMode::ZeroPage};
    constexpr Definition Absolute  = {0xCC, Instruction::CPY, AddressingMode::Absolute};
  } // namespace CPY

  namespace DEC {
    constexpr Definition ZeroPage  = {0xC6, Instruction::DEC, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX = {0xD6, Instruction::DEC, AddressingMode::ZeroPageX};
    constexpr Definition Absolute  = {0xCE, Instruction::DEC, AddressingMode::Absolute};
    constexpr Definition AbsoluteX = {0xDE, Instruction::DEC, AddressingMode::AbsoluteX};
  } // namespace DEC

  namespace DEX {
    constexpr Definition Implied = {0xCA, Instruction::DEX, AddressingMode::Implied};

  } // namespace DEX

  namespace DEY {
    constexpr Definition Implied = {0x88, Instruction::DEY, AddressingMode::Implied};
  } // namespace DEY

  namespace EOR {
    constexpr Definition Immediate       = {0x49, Instruction::EOR, AddressingMode::Immediate};
    constexpr Definition ZeroPage        = {0x45, Instruction::EOR, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX       = {0x55, Instruction::EOR, AddressingMode::ZeroPageX};
    constexpr Definition Absolute        = {0x4D, Instruction::EOR, AddressingMode::Absolute};
    constexpr Definition AbsoluteX       = {0x5D, Instruction::EOR, AddressingMode::AbsoluteX};
    constexpr Definition AbsoluteY       = {0x59, Instruction::EOR, AddressingMode::AbsoluteY};
    constexpr Definition IndexedIndirect = {0x41, Instruction::EOR, AddressingMode::IndexedIndirect};
    constexpr Definition IndirectIndexed = {0x51, Instruction::EOR, AddressingMode::IndirectIndexed};
  } // namespace EOR

  namespace INC {
    constexpr Definition ZeroPage  = {0xE6, Instruction::INC, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX = {0xF6, Instruction::INC, AddressingMode::ZeroPageX};
    constexpr Definition Absolute  = {0xEE, Instruction::INC, AddressingMode::Absolute};
    constexpr Definition AbsoluteX = {0xFE, Instruction::INC, AddressingMode::AbsoluteX};
  } // namespace INC

  namespace INX {
    constexpr Definition Implied = {0xE8, Instruction::INX, AddressingMode::Implied};
  }

  namespace INY {
    constexpr Definition Implied = {0xC8, Instruction::INY, AddressingMode::Implied};
  }

  namespace JMP {
    constexpr Definition Absolute = {0x4C, Instruction::JMP, AddressingMode::Absolute};
    constexpr Definition Indirect = {0x6C, Instruction::JMP, AddressingMode::Indirect};
  } // namespace JMP

  namespace JSR {
    constexpr Definition Absolute = {0x20, Instruction::JSR, AddressingMode::Absolute};
  }

  namespace LDA {
    constexpr Definition Immediate       = {0xA9, Instruction::LDA, AddressingMode::Immediate};
    constexpr Definition ZeroPage        = {0xA5, Instruction::LDA, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX       = {0xB5, Instruction::LDA, AddressingMode::ZeroPageX};
    constexpr Definition Absolute        = {0xAD, Instruction::LDA, AddressingMode::Absolute};
    constexpr Definition AbsoluteX       = {0xBD, Instruction::LDA, AddressingMode::AbsoluteX};
    constexpr Definition AbsoluteY       = {0xB9, Instruction::LDA, AddressingMode::AbsoluteY};
    constexpr Definition IndexedIndirect = {0xA1, Instruction::LDA, AddressingMode::IndexedIndirect};
    constexpr Definition IndirectIndexed = {0xB1, Instruction::LDA, AddressingMode::IndirectIndexed};
  } // namespace LDA

  namespace LDX {
    constexpr Definition Immediate = {0xA2, Instruction::LDX, AddressingMode::Immediate};
    constexpr Definition ZeroPage  = {0xA6, Instruction::LDX, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageY = {0xB6, Instruction::LDX, AddressingMode::ZeroPageY};
    constexpr Definition Absolute  = {0xAE, Instruction::LDX, AddressingMode::Absolute};
    constexpr Definition AbsoluteY = {0xBE, Instruction::LDX, AddressingMode::AbsoluteY};
  } // namespace LDX

  namespace LDY {
    constexpr Definition Immediate = {0xA0, Instruction::LDY, AddressingMode::Immediate};
    constexpr Definition ZeroPage  = {0xA4, Instruction::LDY, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX = {0xB4, Instruction::LDY, AddressingMode::ZeroPageX};
    constexpr Definition Absolute  = {0xAC, Instruction::LDY, AddressingMode::Absolute};
    constexpr Definition AbsoluteX = {0xBC, Instruction::LDY, AddressingMode::AbsoluteX};
  } // namespace LDY

  namespace LSR {
    constexpr Definition Accumulator = {0x4A, Instruction::LSR, AddressingMode::Accumulator};
    constexpr Definition ZeroPage    = {0x46, Instruction::LSR, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX   = {0x56, Instruction::LSR, AddressingMode::ZeroPageX};
    constexpr Definition Absolute    = {0x4E, Instruction::LSR, AddressingMode::Absolute};
    constexpr Definition AbsoluteX   = {0x5E, Instruction::LSR, AddressingMode::AbsoluteX};
  } // namespace LSR

  namespace NOP {
    constexpr Definition Implied = {0xEA, Instruction::NOP, AddressingMode::Implied};
  }

  namespace ORA {
    constexpr Definition Immediate       = {0x09, Instruction::ORA, AddressingMode::Immediate};
    constexpr Definition ZeroPage        = {0x05, Instruction::ORA, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX       = {0x15, Instruction::ORA, AddressingMode::ZeroPageX};
    constexpr Definition Absolute        = {0x0D, Instruction::ORA, AddressingMode::Absolute};
    constexpr Definition AbsoluteX       = {0x1D, Instruction::ORA, AddressingMode::AbsoluteX};
    constexpr Definition AbsoluteY       = {0x19, Instruction::ORA, AddressingMode::AbsoluteY};
    constexpr Definition IndexedIndirect = {0x01, Instruction::ORA, AddressingMode::IndexedIndirect};
    constexpr Definition IndirectIndexed = {0x11, Instruction::ORA, AddressingMode::IndirectIndexed};
  } // namespace ORA

  namespace PHA {
    constexpr Definition Implied = {0x48, Instruction::PHA, AddressingMode::Implied};
  }

  namespace PHP {
    constexpr Definition Implied = {0x08, Instruction::PHP, AddressingMode::Implied};
  }

  namespace PLA {
    constexpr Definition Implied = {0x68, Instruction::PLA, AddressingMode::Implied};
  }

  namespace PLP {
    constexpr Definition Implied = {0x28, Instruction::PLP, AddressingMode::Implied};
  }

  namespace ROL {
    constexpr Definition Accumulator = {0x2A, Instruction::ROL, AddressingMode::Accumulator};
    constexpr Definition ZeroPage    = {0x26, Instruction::ROL, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX   = {0x36, Instruction::ROL, AddressingMode::ZeroPageX};
    constexpr Definition Absolute    = {0x2E, Instruction::ROL, AddressingMode::Absolute};
    constexpr Definition AbsoluteX   = {0x3E, Instruction::ROL, AddressingMode::AbsoluteX};
  } // namespace ROL

  namespace ROR {
    constexpr Definition Accumulator = {0x6A, Instruction::ROR, AddressingMode::Accumulator};
    constexpr Definition ZeroPage    = {0x66, Instruction::ROR, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX   = {0x76, Instruction::ROR, AddressingMode::ZeroPageX};
    constexpr Definition Absolute    = {0x6E, Instruction::ROR, AddressingMode::Absolute};
    constexpr Definition AbsoluteX   = {0x7E, Instruction::ROR, AddressingMode::AbsoluteX};
  } // namespace ROR

  namespace RTI {
    constexpr Definition Implied = {0x40, Instruction::RTI, AddressingMode::Implied};
  }

  namespace RTS {
    constexpr Definition Implied = {0x60, Instruction::RTS, AddressingMode::Implied};
  }

  namespace SBC {
    constexpr Definition Immediate       = {0xE9, Instruction::SBC, AddressingMode::Immediate};
    constexpr Definition ZeroPage        = {0xE5, Instruction::SBC, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX       = {0xF5, Instruction::SBC, AddressingMode::ZeroPageX};
    constexpr Definition Absolute        = {0xED, Instruction::SBC, AddressingMode::Absolute};
    constexpr Definition AbsoluteX       = {0xFD, Instruction::SBC, AddressingMode::AbsoluteX};
    constexpr Definition AbsoluteY       = {0xF9, Instruction::SBC, AddressingMode::AbsoluteY};
    constexpr Definition IndexedIndirect = {0xE1, Instruction::SBC, AddressingMode::IndexedIndirect};
    constexpr Definition IndirectIndexed = {0xF1, Instruction::SBC, AddressingMode::IndirectIndexed};
  } // namespace SBC

  namespace SEC {
    constexpr Definition Implied = {0x38, Instruction::SEC, AddressingMode::Implied};
  }

  namespace SED {
    constexpr Definition Implied = {0xF8, Instruction::SED, AddressingMode::Implied};
  }

  namespace SEI {
    constexpr Definition Implied = {0x78, Instruction::SEI, AddressingMode::Implied};
  }

  namespace STA {
    constexpr Definition ZeroPage        = {0x85, Instruction::STA, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX       = {0x95, Instruction::STA, AddressingMode::ZeroPageX};
    constexpr Definition Absolute        = {0x8D, Instruction::STA, AddressingMode::Absolute};
    constexpr Definition AbsoluteX       = {0x9D, Instruction::STA, AddressingMode::AbsoluteX};
    constexpr Definition AbsoluteY       = {0x99, Instruction::STA, AddressingMode::AbsoluteY};
    constexpr Definition IndexedIndirect = {0x81, Instruction::STA, AddressingMode::IndexedIndirect};
    constexpr Definition IndirectIndexed = {0x91, Instruction::STA, AddressingMode::IndirectIndexed};
  } // namespace STA

  namespace STX {
    constexpr Definition ZeroPage  = {0x86, Instruction::STX, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageY = {0x96, Instruction::STX, AddressingMode::ZeroPageY};
    constexpr Definition Absolute  = {0x8E, Instruction::STX, AddressingMode::Absolute};
  } // namespace STX

  namespace STY {
    constexpr Definition ZeroPage  = {0x84, Instruction::STY, AddressingMode::ZeroPage};
    constexpr Definition ZeroPageX = {0x94, Instruction::STY, AddressingMode::ZeroPageX};
    constexpr Definition Absolute  = {0x8C, Instruction::STY, AddressingMode::Absolute};
  } // namespace STY

  namespace TAX {
    constexpr Definition Implied = {0xAA, Instruction::TAX, AddressingMode::Implied};
  }

  namespace TAY {
    constexpr Definition Implied = {0xA8, Instruction::TAY, AddressingMode::Implied};
  }

  namespace TSX {
    constexpr Definition Implied = {0xBA, Instruction::TSX, AddressingMode::Implied};
  }

  namespace TXA {
    constexpr Definition Implied = {0x8A, Instruction::TXA, AddressingMode::Implied};
  }

  namespace TXS {
    constexpr Definition Implied = {0x9A, Instruction::TXS, AddressingMode::Implied};
  }

  namespace TYA {
    constexpr Definition Implied = {0x98, Instruction::TYA, AddressingMode::Implied};
  } // namespace TYA

  struct OpCodeOld {
    Instruction instruction{Instruction::Unimplemented};
    AddressingMode mode;
  };
} // namespace OpCode
