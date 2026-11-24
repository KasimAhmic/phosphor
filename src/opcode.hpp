#pragma once

#include <cstdint>

#include "addressing_mode.hpp"
#include "instruction.hpp"

namespace OpCode {

  /**
   * TODO: Technically, the Instruction and the AddressingMode are encoded in the namespace and the name of the OpCode's
   * themselves, so I may not even need to store them here. That said, storing them like this makes it easier to work
   * with OpCodes programmatically should that need arise. Long term, I should investigate whether I need Instruction
   * and AddressingMode here at all, or if I can get away with just the code.
   *
   */
  struct Definition {
    std::uint8_t code;
    Instruction instruction;
    AddressingMode mode;

    constexpr operator std::uint8_t() const noexcept { return code; }
    constexpr operator Instruction() const noexcept { return instruction; }
    constexpr operator AddressingMode() const noexcept { return mode; }

    constexpr bool operator==(Definition other) const noexcept {
      return code == other.code && instruction == other.instruction && mode == other.mode;
    }
  };

  namespace ADC {
    inline constexpr Definition Immediate       = {0x69, Instruction::ADC, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage        = {0x65, Instruction::ADC, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX       = {0x75, Instruction::ADC, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute        = {0x6D, Instruction::ADC, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX       = {0x7D, Instruction::ADC, AddressingMode::AbsoluteX};
    inline constexpr Definition AbsoluteY       = {0x79, Instruction::ADC, AddressingMode::AbsoluteY};
    inline constexpr Definition IndexedIndirect = {0x61, Instruction::ADC, AddressingMode::IndexedIndirect};
    inline constexpr Definition IndirectIndexed = {0x71, Instruction::ADC, AddressingMode::IndirectIndexed};
  } // namespace ADC

  namespace AND {
    inline constexpr Definition Immediate       = {0x29, Instruction::AND, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage        = {0x25, Instruction::AND, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX       = {0x35, Instruction::AND, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute        = {0x2D, Instruction::AND, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX       = {0x3D, Instruction::AND, AddressingMode::AbsoluteX};
    inline constexpr Definition AbsoluteY       = {0x39, Instruction::AND, AddressingMode::AbsoluteY};
    inline constexpr Definition IndexedIndirect = {0x21, Instruction::AND, AddressingMode::IndexedIndirect};
    inline constexpr Definition IndirectIndexed = {0x31, Instruction::AND, AddressingMode::IndirectIndexed};

  } // namespace AND

  namespace ASL {
    inline constexpr Definition Accumulator = {0x0A, Instruction::ASL, AddressingMode::Accumulator};
    inline constexpr Definition ZeroPage    = {0x06, Instruction::ASL, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX   = {0x16, Instruction::ASL, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute    = {0x0E, Instruction::ASL, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX   = {0x1E, Instruction::ASL, AddressingMode::AbsoluteX};
  } // namespace ASL

  namespace BCC {
    inline constexpr Definition Relative = {0x90, Instruction::BCC, AddressingMode::Relative};
  } // namespace BCC

  namespace BCS {
    inline constexpr Definition Relative = {0xB0, Instruction::BCS, AddressingMode::Relative};
  } // namespace BCS

  namespace BEQ {
    inline constexpr Definition Relative = {0xF0, Instruction::BEQ, AddressingMode::Relative};
  } // namespace BEQ

  namespace BIT {
    inline constexpr Definition ZeroPage = {0x24, Instruction::BIT, AddressingMode::ZeroPage};
    inline constexpr Definition Absolute = {0x2C, Instruction::BIT, AddressingMode::Absolute};
  } // namespace BIT

  namespace BMI {
    inline constexpr Definition Relative = {0x30, Instruction::BMI, AddressingMode::Relative};
  } // namespace BMI

  namespace BNE {
    inline constexpr Definition Relative = {0xD0, Instruction::BNE, AddressingMode::Relative};
  } // namespace BNE

  namespace BPL {
    inline constexpr Definition Relative = {0x10, Instruction::BPL, AddressingMode::Relative};
  } // namespace BPL

  namespace BRK {
    inline constexpr Definition Implied = {0x00, Instruction::BRK, AddressingMode::Implied};
  } // namespace BRK

  namespace BVC {
    inline constexpr Definition Relative = {0x50, Instruction::BVC, AddressingMode::Relative};
  } // namespace BVC

  namespace BVS {
    inline constexpr Definition Relative = {0x70, Instruction::BVS, AddressingMode::Relative};
  } // namespace BVS

  namespace CLC {
    inline constexpr Definition Implied = {0x18, Instruction::CLC, AddressingMode::Implied};
  } // namespace CLC

  namespace CLD {
    inline constexpr Definition Implied = {0xD8, Instruction::CLD, AddressingMode::Implied};
  } // namespace CLD

  namespace CLI {
    inline constexpr Definition Implied = {0x58, Instruction::CLI, AddressingMode::Implied};
  } // namespace CLI

  namespace CLV {
    inline constexpr Definition Implied = {0xB8, Instruction::CLV, AddressingMode::Implied};
  } // namespace CLV

  namespace CMP {
    inline constexpr Definition Immediate       = {0xC9, Instruction::CMP, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage        = {0xC5, Instruction::CMP, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX       = {0xD5, Instruction::CMP, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute        = {0xCD, Instruction::CMP, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX       = {0xDD, Instruction::CMP, AddressingMode::AbsoluteX};
    inline constexpr Definition AbsoluteY       = {0xD9, Instruction::CMP, AddressingMode::AbsoluteY};
    inline constexpr Definition IndexedIndirect = {0xC1, Instruction::CMP, AddressingMode::IndexedIndirect};
    inline constexpr Definition IndirectIndexed = {0xD1, Instruction::CMP, AddressingMode::IndirectIndexed};
  } // namespace CMP

  namespace CPX {
    inline constexpr Definition Immediate = {0xE0, Instruction::CPX, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage  = {0xE4, Instruction::CPX, AddressingMode::ZeroPage};
    inline constexpr Definition Absolute  = {0xEC, Instruction::CPX, AddressingMode::Absolute};
  } // namespace CPX

  namespace CPY {
    inline constexpr Definition Immediate = {0xC0, Instruction::CPY, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage  = {0xC4, Instruction::CPY, AddressingMode::ZeroPage};
    inline constexpr Definition Absolute  = {0xCC, Instruction::CPY, AddressingMode::Absolute};
  } // namespace CPY

  namespace DEC {
    inline constexpr Definition ZeroPage  = {0xC6, Instruction::DEC, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX = {0xD6, Instruction::DEC, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute  = {0xCE, Instruction::DEC, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX = {0xDE, Instruction::DEC, AddressingMode::AbsoluteX};
  } // namespace DEC

  namespace DEX {
    inline constexpr Definition Implied = {0xCA, Instruction::DEX, AddressingMode::Implied};

  } // namespace DEX

  namespace DEY {
    inline constexpr Definition Implied = {0x88, Instruction::DEY, AddressingMode::Implied};
  } // namespace DEY

  namespace EOR {
    inline constexpr Definition Immediate       = {0x49, Instruction::EOR, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage        = {0x45, Instruction::EOR, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX       = {0x55, Instruction::EOR, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute        = {0x4D, Instruction::EOR, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX       = {0x5D, Instruction::EOR, AddressingMode::AbsoluteX};
    inline constexpr Definition AbsoluteY       = {0x59, Instruction::EOR, AddressingMode::AbsoluteY};
    inline constexpr Definition IndexedIndirect = {0x41, Instruction::EOR, AddressingMode::IndexedIndirect};
    inline constexpr Definition IndirectIndexed = {0x51, Instruction::EOR, AddressingMode::IndirectIndexed};
  } // namespace EOR

  namespace INC {
    inline constexpr Definition ZeroPage  = {0xE6, Instruction::INC, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX = {0xF6, Instruction::INC, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute  = {0xEE, Instruction::INC, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX = {0xFE, Instruction::INC, AddressingMode::AbsoluteX};
  } // namespace INC

  namespace INX {
    inline constexpr Definition Implied = {0xE8, Instruction::INX, AddressingMode::Implied};
  } // namespace INX

  namespace INY {
    inline constexpr Definition Implied = {0xC8, Instruction::INY, AddressingMode::Implied};
  } // namespace INY

  namespace JMP {
    inline constexpr Definition Absolute = {0x4C, Instruction::JMP, AddressingMode::Absolute};
    inline constexpr Definition Indirect = {0x6C, Instruction::JMP, AddressingMode::Indirect};
  } // namespace JMP

  namespace JSR {
    inline constexpr Definition Absolute = {0x20, Instruction::JSR, AddressingMode::Absolute};
  } // namespace JSR

  namespace LDA {
    inline constexpr Definition Immediate       = {0xA9, Instruction::LDA, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage        = {0xA5, Instruction::LDA, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX       = {0xB5, Instruction::LDA, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute        = {0xAD, Instruction::LDA, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX       = {0xBD, Instruction::LDA, AddressingMode::AbsoluteX};
    inline constexpr Definition AbsoluteY       = {0xB9, Instruction::LDA, AddressingMode::AbsoluteY};
    inline constexpr Definition IndexedIndirect = {0xA1, Instruction::LDA, AddressingMode::IndexedIndirect};
    inline constexpr Definition IndirectIndexed = {0xB1, Instruction::LDA, AddressingMode::IndirectIndexed};
  } // namespace LDA

  namespace LDX {
    inline constexpr Definition Immediate = {0xA2, Instruction::LDX, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage  = {0xA6, Instruction::LDX, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageY = {0xB6, Instruction::LDX, AddressingMode::ZeroPageY};
    inline constexpr Definition Absolute  = {0xAE, Instruction::LDX, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteY = {0xBE, Instruction::LDX, AddressingMode::AbsoluteY};
  } // namespace LDX

  namespace LDY {
    inline constexpr Definition Immediate = {0xA0, Instruction::LDY, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage  = {0xA4, Instruction::LDY, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX = {0xB4, Instruction::LDY, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute  = {0xAC, Instruction::LDY, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX = {0xBC, Instruction::LDY, AddressingMode::AbsoluteX};
  } // namespace LDY

  namespace LSR {
    inline constexpr Definition Accumulator = {0x4A, Instruction::LSR, AddressingMode::Accumulator};
    inline constexpr Definition ZeroPage    = {0x46, Instruction::LSR, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX   = {0x56, Instruction::LSR, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute    = {0x4E, Instruction::LSR, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX   = {0x5E, Instruction::LSR, AddressingMode::AbsoluteX};
  } // namespace LSR

  namespace NOP {
    inline constexpr Definition Implied = {0xEA, Instruction::NOP, AddressingMode::Implied};
  } // namespace NOP

  namespace ORA {
    inline constexpr Definition Immediate       = {0x09, Instruction::ORA, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage        = {0x05, Instruction::ORA, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX       = {0x15, Instruction::ORA, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute        = {0x0D, Instruction::ORA, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX       = {0x1D, Instruction::ORA, AddressingMode::AbsoluteX};
    inline constexpr Definition AbsoluteY       = {0x19, Instruction::ORA, AddressingMode::AbsoluteY};
    inline constexpr Definition IndexedIndirect = {0x01, Instruction::ORA, AddressingMode::IndexedIndirect};
    inline constexpr Definition IndirectIndexed = {0x11, Instruction::ORA, AddressingMode::IndirectIndexed};
  } // namespace ORA

  namespace PHA {
    inline constexpr Definition Implied = {0x48, Instruction::PHA, AddressingMode::Implied};
  } // namespace PHA

  namespace PHP {
    inline constexpr Definition Implied = {0x08, Instruction::PHP, AddressingMode::Implied};
  } // namespace PHP

  namespace PLA {
    inline constexpr Definition Implied = {0x68, Instruction::PLA, AddressingMode::Implied};
  } // namespace PLA

  namespace PLP {
    inline constexpr Definition Implied = {0x28, Instruction::PLP, AddressingMode::Implied};
  } // namespace PLP

  namespace ROL {
    inline constexpr Definition Accumulator = {0x2A, Instruction::ROL, AddressingMode::Accumulator};
    inline constexpr Definition ZeroPage    = {0x26, Instruction::ROL, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX   = {0x36, Instruction::ROL, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute    = {0x2E, Instruction::ROL, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX   = {0x3E, Instruction::ROL, AddressingMode::AbsoluteX};
  } // namespace ROL

  namespace ROR {
    inline constexpr Definition Accumulator = {0x6A, Instruction::ROR, AddressingMode::Accumulator};
    inline constexpr Definition ZeroPage    = {0x66, Instruction::ROR, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX   = {0x76, Instruction::ROR, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute    = {0x6E, Instruction::ROR, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX   = {0x7E, Instruction::ROR, AddressingMode::AbsoluteX};
  } // namespace ROR

  namespace RTI {
    inline constexpr Definition Implied = {0x40, Instruction::RTI, AddressingMode::Implied};
  } // namespace RTI

  namespace RTS {
    inline constexpr Definition Implied = {0x60, Instruction::RTS, AddressingMode::Implied};
  } // namespace RTS

  namespace SBC {
    inline constexpr Definition Immediate       = {0xE9, Instruction::SBC, AddressingMode::Immediate};
    inline constexpr Definition ZeroPage        = {0xE5, Instruction::SBC, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX       = {0xF5, Instruction::SBC, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute        = {0xED, Instruction::SBC, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX       = {0xFD, Instruction::SBC, AddressingMode::AbsoluteX};
    inline constexpr Definition AbsoluteY       = {0xF9, Instruction::SBC, AddressingMode::AbsoluteY};
    inline constexpr Definition IndexedIndirect = {0xE1, Instruction::SBC, AddressingMode::IndexedIndirect};
    inline constexpr Definition IndirectIndexed = {0xF1, Instruction::SBC, AddressingMode::IndirectIndexed};
  } // namespace SBC

  namespace SEC {
    inline constexpr Definition Implied = {0x38, Instruction::SEC, AddressingMode::Implied};
  } // namespace SEC

  namespace SED {
    inline constexpr Definition Implied = {0xF8, Instruction::SED, AddressingMode::Implied};
  } // namespace SED

  namespace SEI {
    inline constexpr Definition Implied = {0x78, Instruction::SEI, AddressingMode::Implied};
  } // namespace SEI

  namespace STA {
    inline constexpr Definition ZeroPage        = {0x85, Instruction::STA, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX       = {0x95, Instruction::STA, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute        = {0x8D, Instruction::STA, AddressingMode::Absolute};
    inline constexpr Definition AbsoluteX       = {0x9D, Instruction::STA, AddressingMode::AbsoluteX};
    inline constexpr Definition AbsoluteY       = {0x99, Instruction::STA, AddressingMode::AbsoluteY};
    inline constexpr Definition IndexedIndirect = {0x81, Instruction::STA, AddressingMode::IndexedIndirect};
    inline constexpr Definition IndirectIndexed = {0x91, Instruction::STA, AddressingMode::IndirectIndexed};
  } // namespace STA

  namespace STX {
    inline constexpr Definition ZeroPage  = {0x86, Instruction::STX, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageY = {0x96, Instruction::STX, AddressingMode::ZeroPageY};
    inline constexpr Definition Absolute  = {0x8E, Instruction::STX, AddressingMode::Absolute};
  } // namespace STX

  namespace STY {
    inline constexpr Definition ZeroPage  = {0x84, Instruction::STY, AddressingMode::ZeroPage};
    inline constexpr Definition ZeroPageX = {0x94, Instruction::STY, AddressingMode::ZeroPageX};
    inline constexpr Definition Absolute  = {0x8C, Instruction::STY, AddressingMode::Absolute};
  } // namespace STY

  namespace TAX {
    inline constexpr Definition Implied = {0xAA, Instruction::TAX, AddressingMode::Implied};
  } // namespace TAX

  namespace TAY {
    inline constexpr Definition Implied = {0xA8, Instruction::TAY, AddressingMode::Implied};
  } // namespace TAY

  namespace TSX {
    inline constexpr Definition Implied = {0xBA, Instruction::TSX, AddressingMode::Implied};
  } // namespace TSX

  namespace TXA {
    inline constexpr Definition Implied = {0x8A, Instruction::TXA, AddressingMode::Implied};
  } // namespace TXA

  namespace TXS {
    inline constexpr Definition Implied = {0x9A, Instruction::TXS, AddressingMode::Implied};
  } // namespace TXS

  namespace TYA {
    inline constexpr Definition Implied = {0x98, Instruction::TYA, AddressingMode::Implied};
  } // namespace TYA

  namespace Unofficial {
    namespace NOP {
      inline constexpr Definition ZeroPage1 = {0x04, Instruction::NOP, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPage2 = {0x44, Instruction::NOP, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPage3 = {0x64, Instruction::NOP, AddressingMode::ZeroPage};

      inline constexpr Definition Absolute = {0x0C, Instruction::NOP, AddressingMode::Absolute};

      inline constexpr Definition ZeroPageX1 = {0x14, Instruction::NOP, AddressingMode::ZeroPageX};
      inline constexpr Definition ZeroPageX2 = {0x34, Instruction::NOP, AddressingMode::ZeroPageX};
      inline constexpr Definition ZeroPageX3 = {0x54, Instruction::NOP, AddressingMode::ZeroPageX};
      inline constexpr Definition ZeroPageX4 = {0x74, Instruction::NOP, AddressingMode::ZeroPageX};
      inline constexpr Definition ZeroPageX5 = {0xD4, Instruction::NOP, AddressingMode::ZeroPageX};
      inline constexpr Definition ZeroPageX6 = {0xF4, Instruction::NOP, AddressingMode::ZeroPageX};

      inline constexpr Definition Implied1 = {0x1A, Instruction::NOP, AddressingMode::Implied};
      inline constexpr Definition Implied2 = {0x3A, Instruction::NOP, AddressingMode::Implied};
      inline constexpr Definition Implied3 = {0x5A, Instruction::NOP, AddressingMode::Implied};
      inline constexpr Definition Implied4 = {0x7A, Instruction::NOP, AddressingMode::Implied};
      inline constexpr Definition Implied5 = {0xDA, Instruction::NOP, AddressingMode::Implied};
      inline constexpr Definition Implied6 = {0xFA, Instruction::NOP, AddressingMode::Implied};

      inline constexpr Definition Immediate1 = {0x80, Instruction::NOP, AddressingMode::Immediate};
      inline constexpr Definition Immediate2 = {0x82, Instruction::NOP, AddressingMode::Immediate};
      inline constexpr Definition Immediate3 = {0x89, Instruction::NOP, AddressingMode::Immediate};
      inline constexpr Definition Immediate4 = {0xC2, Instruction::NOP, AddressingMode::Immediate};
      inline constexpr Definition Immediate5 = {0xE2, Instruction::NOP, AddressingMode::Immediate};

      inline constexpr Definition AbsoluteX1 = {0x1C, Instruction::NOP, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteX2 = {0x3C, Instruction::NOP, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteX3 = {0x5C, Instruction::NOP, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteX4 = {0x7C, Instruction::NOP, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteX5 = {0xDC, Instruction::NOP, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteX6 = {0xFC, Instruction::NOP, AddressingMode::AbsoluteX};
    } // namespace NOP
  } // namespace Unofficial
} // namespace OpCode
