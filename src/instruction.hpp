#pragma once

#include <cstdint>

enum class Instruction : std::uint8_t {
  /**
   * @brief Add with Carry
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#ADC
   */
  ADC,

  /**
   * @brief Bitwise AND
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#AND
   */
  AND,

  /**
   * @brief Arithmetic Shift Left
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#ASL
   */
  ASL,

  /**
   * @brief Branch if Carry Clear
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BCC
   */
  BCC,

  /**
   * @brief Branch if Carry Set
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BCS
   */
  BCS,

  /**
   * @brief Branch if Equal
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BEQ
   */
  BEQ,

  /**
   * @brief Bit Test
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BIT
   */
  BIT,

  /**
   * @brief Branch if Minus
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BMI
   */
  BMI,

  /**
   * @brief Branch if Not Equal
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BNE
   */
  BNE,

  /**
   * @brief Branch if Plus
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BPL
   */
  BPL,

  /**
   * @brief Break (software IRQ)
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BRK
   */
  BRK,

  /**
   * @brief Branch if Overflow Clear
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BVC
   */
  BVC,

  /**
   * @brief Branch if Overflow Set
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#BVS
   */
  BVS,

  /**
   * @brief Clear Carry
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#CLC
   */
  CLC,

  /**
   * @brief Clear Decimal
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#CDL
   */
  CLD,

  /**
   * @brief Clear Interrupt Disable
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#CLI
   */
  CLI,

  /**
   * @brief Clear Overflow
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#CLV
   */
  CLV,

  /**
   * @brief Compare A
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#CMP
   */
  CMP,

  /**
   * @brief Compare X
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#CPX
   */
  CPX,

  /**
   * @brief Compare Y
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#CPY
   */
  CPY,

  /**
   * @brief Decrement Memory
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#DEC
   */
  DEC,

  /**
   * @brief Decrement X
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#DEX
   */
  DEX,

  /**
   * @brief Decrement Y
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#DEY
   */
  DEY,

  /**
   * @brief Bitwise Exclusive OR
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#EOR
   */
  EOR,

  /**
   * @brief Increment Memory
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#INC
   */
  INC,

  /**
   * @brief Increment X
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#INX
   */
  INX,

  /**
   * @brief Increment Y
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#INY
   */
  INY,

  /**
   * @brief Jump
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#JMP
   */
  JMP,

  /**
   * @brief Jump to Subroutine
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#JSR
   */
  JSR,

  /**
   * @brief Load A
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#LDA
   */
  LDA,

  /**
   * @brief Load X
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#LDX
   */
  LDX,

  /**
   * @brief Load Y
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#LDY
   */
  LDY,

  /**
   * @brief Logical Shift Right
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#LSR
   */
  LSR,

  /**
   * @brief No Operation
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#NOP
   */
  NOP,

  /**
   * @brief Bitwise OR
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#ORA
   */
  ORA,

  /**
   * @brief Push A
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#PHA
   */
  PHA,

  /**
   * @brief Push Processor Status
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#PHP
   */
  PHP,

  /**
   * @brief Pull A
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#PLA
   */
  PLA,

  /**
   * @brief Pull Processor Status
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#PLP
   */
  PLP,

  /**
   * @brief Rotate Left
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#ROL
   */
  ROL,

  /**
   * @brief Rotate Right
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#ROR
   */
  ROR,

  /**
   * @brief Return from Interrupt
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#RTI
   */
  RTI,

  /**
   * @brief Return from Subroutine
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#RTS
   */
  RTS,

  /**
   * @brief Subtract with Carry
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#SBC
   */
  SBC,

  /**
   * @brief Set Carry
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#SEC
   */
  SEC,

  /**
   * @brief Set Decimal
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#SED
   */
  SED,

  /**
   * @brief Set Interrupt Disable
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#SEI
   */
  SEI,

  /**
   * @brief Store A
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#STA
   */
  STA,

  /**
   * @brief Store X
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#STX
   */
  STX,

  /**
   * @brief Store Y
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#STY
   */
  STY,

  /**
   * @brief Transfer A to X
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#TAX
   */
  TAX,

  /**
   * @brief Transfer A to Y
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#TAY
   */
  TAY,

  /**
   * @brief Transfer Stack Pointer to X
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#TSX
   */
  TSX,

  /**
   * @brief Transfer X to A
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#TXA
   */
  TXA,

  /**
   * @brief Transfer X to Stack Pointer
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#TXS
   */
  TXS,

  /**
   * @brief Transfer Y to A
   *
   * @see https://www.nesdev.org/wiki/Instruction_reference#TYA
   */
  TYA,

  /**
   * @brief UNOFFICIAL OPCODE. A &= immediate, C becomes bit 7 of A.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  ANC,

  /**
   * @brief UNOFFICIAL OPCODE. A &= immediate, then logical shift right.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  ALR,

  /**
   * @brief UNOFFICIAL OPCODE. A &= immediate, then rotate right through carry.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  ARR,

  /**
   * @brief UNOFFICIAL OPCODE.X = (A & X) - immediate.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  AXS,

  /**
   * @brief UNOFFICIAL OPCODE. Equivalent to DEC + CMP.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  DCP,

  /**
   * @brief UNOFFICIAL OPCODE. Equivalent to INC + SBC.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  ISC,

  /**
   * @brief UNOFFICIAL OPCODE. Load A and X.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  LAX,

  /**
   * @brief UNOFFICIAL OPCODE. Equivalent to ROL + AND.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  RLA,

  /**
   * @brief UNOFFICIAL OPCODE. Equivalent to ROR + ADC.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  RRA,

  /**
   * @brief UNOFFICIAL OPCODE. Store A & X.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  SAX,

  /**
   * @brief UNOFFICIAL OPCODE. Equivalent to ASL + ORA.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  SLO,

  /**
   * @brief UNOFFICIAL OPCODE. Equivalent to LSR + EOR.
   *
   * @see https://www.nesdev.org/wiki/CPU_unofficial_opcodes
   */
  SRE,
};
