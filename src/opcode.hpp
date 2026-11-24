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
    namespace ANC {
      inline constexpr Definition Immediate1 = {0x0B, Instruction::ANC, AddressingMode::Immediate};
      inline constexpr Definition Immediate2 = {0x2B, Instruction::ANC, AddressingMode::Immediate};
    } // namespace ANC

    namespace ALR {
      inline constexpr Definition Immediate = {0x4B, Instruction::ALR, AddressingMode::Immediate};
    } // namespace ALR

    namespace ARR {
      inline constexpr Definition Immediate = {0x6B, Instruction::ARR, AddressingMode::Immediate};
    } // namespace ARR

    namespace AXS {
      inline constexpr Definition Immediate = {0xCB, Instruction::AXS, AddressingMode::Immediate};
    } // namespace AXS

    namespace DCP {
      inline constexpr Definition ZeroPage        = {0xC7, Instruction::DCP, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPageX       = {0xD7, Instruction::DCP, AddressingMode::ZeroPageX};
      inline constexpr Definition Absolute        = {0xCF, Instruction::DCP, AddressingMode::Absolute};
      inline constexpr Definition AbsoluteX       = {0xDF, Instruction::DCP, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteY       = {0xDB, Instruction::DCP, AddressingMode::AbsoluteY};
      inline constexpr Definition IndexedIndirect = {0xC3, Instruction::DCP, AddressingMode::IndexedIndirect};
      inline constexpr Definition IndirectIndexed = {0xD3, Instruction::DCP, AddressingMode::IndirectIndexed};
    } // namespace DCP

    namespace ISC {
      inline constexpr Definition ZeroPage        = {0xE7, Instruction::ISC, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPageX       = {0xF7, Instruction::ISC, AddressingMode::ZeroPageX};
      inline constexpr Definition Absolute        = {0xEF, Instruction::ISC, AddressingMode::Absolute};
      inline constexpr Definition AbsoluteX       = {0xFF, Instruction::ISC, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteY       = {0xFB, Instruction::ISC, AddressingMode::AbsoluteY};
      inline constexpr Definition IndexedIndirect = {0xE3, Instruction::ISC, AddressingMode::IndexedIndirect};
      inline constexpr Definition IndirectIndexed = {0xF3, Instruction::ISC, AddressingMode::IndirectIndexed};
    } // namespace ISC

    namespace LAX {
      inline constexpr Definition Immediate       = {0xAB, Instruction::LAX, AddressingMode::Immediate};
      inline constexpr Definition ZeroPage        = {0xA7, Instruction::LAX, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPageY       = {0xB7, Instruction::LAX, AddressingMode::ZeroPageY};
      inline constexpr Definition Absolute        = {0xAF, Instruction::LAX, AddressingMode::Absolute};
      inline constexpr Definition AbsoluteY       = {0xBF, Instruction::LAX, AddressingMode::AbsoluteY};
      inline constexpr Definition IndexedIndirect = {0xA3, Instruction::LAX, AddressingMode::IndexedIndirect};
      inline constexpr Definition IndirectIndexed = {0xB3, Instruction::LAX, AddressingMode::IndirectIndexed};
    } // namespace LAX

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

    namespace RLA {
      inline constexpr Definition ZeroPage        = {0x27, Instruction::RLA, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPageX       = {0x37, Instruction::RLA, AddressingMode::ZeroPageX};
      inline constexpr Definition Absolute        = {0x2F, Instruction::RLA, AddressingMode::Absolute};
      inline constexpr Definition AbsoluteX       = {0x3F, Instruction::RLA, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteY       = {0x3B, Instruction::RLA, AddressingMode::AbsoluteY};
      inline constexpr Definition IndexedIndirect = {0x23, Instruction::RLA, AddressingMode::IndexedIndirect};
      inline constexpr Definition IndirectIndexed = {0x33, Instruction::RLA, AddressingMode::IndirectIndexed};
    } // namespace RLA

    namespace RRA {
      inline constexpr Definition ZeroPage        = {0x67, Instruction::RRA, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPageX       = {0x77, Instruction::RRA, AddressingMode::ZeroPageX};
      inline constexpr Definition Absolute        = {0x6F, Instruction::RRA, AddressingMode::Absolute};
      inline constexpr Definition AbsoluteX       = {0x7F, Instruction::RRA, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteY       = {0x7B, Instruction::RRA, AddressingMode::AbsoluteY};
      inline constexpr Definition IndexedIndirect = {0x63, Instruction::RRA, AddressingMode::IndexedIndirect};
      inline constexpr Definition IndirectIndexed = {0x73, Instruction::RRA, AddressingMode::IndirectIndexed};
    } // namespace RRA

    namespace SAX {
      inline constexpr Definition ZeroPage        = {0x87, Instruction::SAX, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPageY       = {0x97, Instruction::SAX, AddressingMode::ZeroPageY};
      inline constexpr Definition Absolute        = {0x8F, Instruction::SAX, AddressingMode::Absolute};
      inline constexpr Definition IndexedIndirect = {0x83, Instruction::SAX, AddressingMode::IndexedIndirect};
    } // namespace SAX

    namespace SBC {
      inline constexpr Definition Immediate = {0xEB, Instruction::SBC, AddressingMode::Immediate};
    } // namespace SBC

    namespace SLO {
      inline constexpr Definition ZeroPage        = {0x07, Instruction::SLO, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPageX       = {0x17, Instruction::SLO, AddressingMode::ZeroPageX};
      inline constexpr Definition Absolute        = {0x0F, Instruction::SLO, AddressingMode::Absolute};
      inline constexpr Definition AbsoluteX       = {0x1F, Instruction::SLO, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteY       = {0x1B, Instruction::SLO, AddressingMode::AbsoluteY};
      inline constexpr Definition IndexedIndirect = {0x03, Instruction::SLO, AddressingMode::IndexedIndirect};
      inline constexpr Definition IndirectIndexed = {0x13, Instruction::SLO, AddressingMode::IndirectIndexed};
    } // namespace SLO

    namespace SRE {
      inline constexpr Definition ZeroPage        = {0x47, Instruction::SRE, AddressingMode::ZeroPage};
      inline constexpr Definition ZeroPageX       = {0x57, Instruction::SRE, AddressingMode::ZeroPageX};
      inline constexpr Definition Absolute        = {0x4F, Instruction::SRE, AddressingMode::Absolute};
      inline constexpr Definition AbsoluteX       = {0x5F, Instruction::SRE, AddressingMode::AbsoluteX};
      inline constexpr Definition AbsoluteY       = {0x5B, Instruction::SRE, AddressingMode::AbsoluteY};
      inline constexpr Definition IndexedIndirect = {0x43, Instruction::SRE, AddressingMode::IndexedIndirect};
      inline constexpr Definition IndirectIndexed = {0x53, Instruction::SRE, AddressingMode::IndirectIndexed};
    } // namespace SRE
  } // namespace Unofficial
} // namespace OpCode
