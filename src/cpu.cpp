#include "cpu.hpp"

#include <ostream>
#include <print>

#include "opcode.hpp"

CPU::CPU(std::array<std::uint8_t, 65536> mem)
    : _registers(), _total_cycle_count{0}, _current_cycle_count{0}, _memory{mem} {}

CPU::~CPU() = default;

void CPU::reset() {
  this->_registers.pc = 0xC000;
  this->_registers.a  = 0x00;
  this->_registers.x  = 0x00;
  this->_registers.y  = 0x00;
  this->_registers.p  = 0x24;
  this->_registers.sp = 0xFD;

  this->_total_cycle_count = 7;
}

std::int8_t CPU::step() {
  this->_current_cycle_count = 0;

  const auto opcode = this->read(this->_registers.pc++);

  switch (opcode) {

  case OpCode::ADC::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::ZeroPage: {
    const std::uint8_t addr  = this->read(this->_registers.pc++);
    const std::uint8_t value = this->read(addr);

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::ZeroPageX: {
    break;
  }

  case OpCode::ADC::Absolute: {
    break;
  }

  case OpCode::ADC::AbsoluteX: {
    break;
  }

  case OpCode::ADC::AbsoluteY: {
    break;
  }

  case OpCode::ADC::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();

    const std::uint8_t value = this->read(addr);

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::IndirectIndexed: {
    break;
  }

  case OpCode::AND::Immediate: {
    const uint8_t value = this->read(this->_registers.pc++);

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::ZeroPage: {
    const std::uint8_t addr  = this->read(this->_registers.pc++);
    const std::uint8_t value = this->read(addr);

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::ZeroPageX: {
    break;
  }

  case OpCode::AND::Absolute: {
    break;
  }

  case OpCode::AND::AbsoluteX: {
    break;
  }

  case OpCode::AND::AbsoluteY: {
    break;
  }

  case OpCode::AND::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();

    const std::uint8_t value = this->read(addr);

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::IndirectIndexed: {
    break;
  }

  case OpCode::ASL::Accumulator: {
    (void)this->read(this->_registers.pc);

    const std::uint8_t carry = this->_registers.a & 0x80;

    this->_registers.a <<= 1;

    this->_registers.set_carry(carry);
    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::ASL::ZeroPage: {
    break;
  }

  case OpCode::ASL::ZeroPageX: {
    break;
  }

  case OpCode::ASL::Absolute: {
    break;
  }

  case OpCode::ASL::AbsoluteX: {
    break;
  }

  case OpCode::BCC::Relative: {
    this->branch_if(this->_registers.is_carry_clear());
    break;
  }

  case OpCode::BCS::Relative: {
    this->branch_if(this->_registers.is_carry_set());
    break;
  }

  case OpCode::BEQ::Relative: {
    this->branch_if(this->_registers.is_zero_set());
    break;
  }

  case OpCode::BIT::ZeroPage: {
    const std::uint8_t addr  = this->read(this->_registers.pc++);
    const std::uint8_t value = this->read(addr);

    const std::uint8_t result = this->_registers.a & value;

    this->_registers.set_zero(result == 0);
    this->_registers.set_overflow(value & 0x40);
    this->_registers.set_negative(value & 0x80);

    break;
  }

  case OpCode::BIT::Absolute: {
    break;
  }

  case OpCode::BMI::Relative: {
    this->branch_if(this->_registers.is_negative_set());
    break;
  }

  case OpCode::BNE::Relative: {
    this->branch_if(this->_registers.is_zero_clear());
    break;
  }

  case OpCode::BPL::Relative: {
    this->branch_if(this->_registers.is_negative_clear());
    break;
  }

  case OpCode::BRK::Implied: {
    break;
  }

  case OpCode::BVC::Relative: {
    this->branch_if(this->_registers.is_overflow_clear());
    break;
  }

  case OpCode::BVS::Relative: {
    this->branch_if(this->_registers.is_overflow_set());
    break;
  }

  case OpCode::CLC::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.set_carry(false);

    break;
  }

  case OpCode::CLD::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.set_decimal_mode(false);

    break;
  }

  case OpCode::CLI::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.set_interrupt_disable(false);

    break;
  }

  case OpCode::CLV::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.set_overflow(false);

    break;
  }

  case OpCode::CMP::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    this->compare(value);

    break;
  }

  case OpCode::CMP::ZeroPage: {
    break;
  }

  case OpCode::CMP::ZeroPageX: {
    break;
  }

  case OpCode::CMP::Absolute: {
    break;
  }

  case OpCode::CMP::AbsoluteX: {
    break;
  }

  case OpCode::CMP::AbsoluteY: {
    break;
  }

  case OpCode::CMP::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();

    const std::uint8_t value = this->read(addr);

    this->compare(value);

    break;
  }

  case OpCode::CMP::IndirectIndexed: {
    break;
  }

  case OpCode::CPX::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    const std::uint8_t result = this->_registers.x - value;

    this->_registers.set_carry(this->_registers.x >= value);
    this->_registers.set_zero(result == 0);
    this->_registers.set_negative(result & 0x80);

    break;
  }

  case OpCode::CPX::ZeroPage: {
    break;
  }

  case OpCode::CPX::Absolute: {
    break;
  }

  case OpCode::CPY::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    const std::uint8_t result = this->_registers.y - value;

    this->_registers.set_carry(this->_registers.y >= value);
    this->_registers.set_zero(result == 0);
    this->_registers.set_negative(result & 0x80);

    break;
  }

  case OpCode::CPY::ZeroPage: {
    break;
  }

  case OpCode::CPY::Absolute: {
    break;
  }

  case OpCode::DEC::ZeroPage: {
    break;
  }

  case OpCode::DEC::ZeroPageX: {
    break;
  }

  case OpCode::DEC::Absolute: {
    break;
  }

  case OpCode::DEC::AbsoluteX: {
    break;
  }

  case OpCode::DEX::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.x--;

    this->_registers.set_zero(this->_registers.x == 0);
    this->_registers.set_negative(this->_registers.x & 0x80);

    break;
  }

  case OpCode::DEY::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.y--;

    this->_registers.set_zero(this->_registers.y == 0);
    this->_registers.set_negative(this->_registers.y & 0x80);

    break;
  }

  case OpCode::EOR::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::EOR::ZeroPage: {
    const std::uint8_t addr  = this->read(this->_registers.pc++);
    const std::uint8_t value = this->read(addr);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::EOR::ZeroPageX: {
    break;
  }

  case OpCode::EOR::Absolute: {
    break;
  }

  case OpCode::EOR::AbsoluteX: {
    break;
  }

  case OpCode::EOR::AbsoluteY: {
    break;
  }

  case OpCode::EOR::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();

    const std::uint8_t value = this->read(addr);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::EOR::IndirectIndexed: {
    break;
  }

  case OpCode::INC::ZeroPage: {
    break;
  }

  case OpCode::INC::ZeroPageX: {
    break;
  }

  case OpCode::INC::Absolute: {
    break;
  }

  case OpCode::INC::AbsoluteX: {
    break;
  }

  case OpCode::INX::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.x++;

    this->_registers.set_zero(this->_registers.x == 0);
    this->_registers.set_negative(this->_registers.x & 0x80);

    break;
  }

  case OpCode::INY::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.y++;

    this->_registers.set_zero(this->_registers.y == 0);
    this->_registers.set_negative(this->_registers.y & 0x80);

    break;
  }

  case OpCode::JMP::Absolute: {
    const auto low  = this->read(_registers.pc++);
    const auto high = this->read(_registers.pc++);

    this->_registers.pc = static_cast<std::uint16_t>(low | (high << 8));

    break;
  }

  case OpCode::JMP::Indirect: {
    break;
  }

  case OpCode::JSR::Absolute: {
    const auto low = this->read(_registers.pc++);
    (void)this->read(0x0100 | this->_registers.sp);

    const auto return_addr = this->_registers.pc;

    this->write(0x0100 | this->_registers.sp--, static_cast<std::uint8_t>(return_addr >> 8));
    this->write(0x0100 | this->_registers.sp--, static_cast<std::uint8_t>(return_addr & 0xFF));

    const auto high = this->read(_registers.pc++);

    this->_registers.pc = static_cast<std::uint16_t>(low | (high << 8));

    break;
  }

  case OpCode::LDA::Immediate: {
    this->_registers.a = this->read(_registers.pc++);

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative((this->_registers.a & 0x80) != 0);

    break;
  }

  case OpCode::LDA::ZeroPage: {
    const std::uint8_t addr = this->read(_registers.pc++);
    this->_registers.a      = this->read(addr);

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::LDA::ZeroPageX: {
    break;
  }

  case OpCode::LDA::Absolute: {
    const std::uint8_t low  = this->read(_registers.pc++);
    const std::uint8_t high = this->read(_registers.pc++);

    const std::uint16_t addr = (high << 8) | low;

    this->_registers.a = this->read(addr);

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::LDA::AbsoluteX: {
    break;
  }

  case OpCode::LDA::AbsoluteY: {
    break;
  }

  case OpCode::LDA::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();

    this->_registers.a = this->read(addr);

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::LDA::IndirectIndexed: {
    break;
  }

  case OpCode::LDX::Immediate: {
    this->_registers.x = this->read(_registers.pc++);

    this->_registers.set_zero(this->_registers.x == 0);
    this->_registers.set_negative(this->_registers.x & 0x80);

    break;
  }

  case OpCode::LDX::ZeroPage: {
    const std::uint8_t addr  = this->read(this->_registers.pc++);
    const std::uint8_t value = this->read(addr);

    this->_registers.x = value;

    this->_registers.set_zero(this->_registers.x == 0);
    this->_registers.set_negative(this->_registers.x & 0x80);
  }

  case OpCode::LDX::ZeroPageY: {
    break;
  }

  case OpCode::LDX::Absolute: {
    const std::uint8_t low  = this->read(_registers.pc++);
    const std::uint8_t high = this->read(_registers.pc++);

    const std::uint16_t addr = (high << 8) | low;

    this->_registers.x = this->read(addr);

    this->_registers.set_zero(this->_registers.x == 0);
    this->_registers.set_negative(this->_registers.x & 0x80);

    break;
  }

  case OpCode::LDX::AbsoluteY: {
    break;
  }

  case OpCode::LDY::Immediate: {
    this->_registers.y = this->read(_registers.pc++);

    this->_registers.set_zero(this->_registers.y == 0);
    this->_registers.set_negative(this->_registers.y & 0x80);

    break;
  }

  case OpCode::LDY::ZeroPage: {
    const std::uint8_t addr  = this->read(this->_registers.pc++);
    const std::uint8_t value = this->read(addr);

    this->_registers.y = value;

    this->_registers.set_zero(this->_registers.y == 0);
    this->_registers.set_negative(this->_registers.y & 0x80);

    break;
  }

  case OpCode::LDY::ZeroPageX: {
    break;
  }

  case OpCode::LDY::Absolute: {
    break;
  }

  case OpCode::LDY::AbsoluteX: {
    break;
  }

  case OpCode::LSR::Accumulator: {
    (void)this->read(this->_registers.pc);

    const std::uint8_t carry = this->_registers.a & 0x01;

    this->_registers.a >>= 1;

    this->_registers.set_carry(carry);
    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(false);

    break;
  }

  case OpCode::LSR::ZeroPage: {
    break;
  }

  case OpCode::LSR::ZeroPageX: {
    break;
  }

  case OpCode::LSR::Absolute: {
    break;
  }

  case OpCode::LSR::AbsoluteX: {
    break;
  }

  case OpCode::NOP::Implied: {
    (void)this->read(this->_registers.pc);

    break;
  }

  case OpCode::ORA::Immediate: {
    const std::uint8_t value = this->read(_registers.pc++);

    this->_registers.a |= value;

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::ORA::ZeroPage: {
    const std::uint8_t addr  = this->read(this->_registers.pc++);
    const std::uint8_t value = this->read(addr);

    this->_registers.a |= value;

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::ORA::ZeroPageX: {
    break;
  }

  case OpCode::ORA::Absolute: {
    break;
  }

  case OpCode::ORA::AbsoluteX: {
    break;
  }

  case OpCode::ORA::AbsoluteY: {
    break;
  }

  case OpCode::ORA::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();

    const std::uint8_t value = this->read(addr);

    this->_registers.a |= value;

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::ORA::IndirectIndexed: {
    break;
  }

  case OpCode::PHA::Implied: {
    (void)this->read(this->_registers.pc);

    this->write(0x0100 | this->_registers.sp--, this->_registers.a);

    break;
  }

  case OpCode::PHP::Implied: {
    (void)this->read(this->_registers.pc);

    this->write(0x0100 | this->_registers.sp--, this->_registers.p | 0x30);

    break;
  }

  case OpCode::PLA::Implied: {
    (void)this->read(this->_registers.pc);
    (void)this->read(0x0100 | this->_registers.sp++);

    this->_registers.a = this->read(0x0100 | this->_registers.sp);

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::PLP::Implied: {
    (void)this->read(this->_registers.pc);
    (void)this->read(0x0100 | this->_registers.sp++);

    this->_registers.p = (this->read(0x0100 | this->_registers.sp) & ~0x10) | 0x20;

    break;
  }

  case OpCode::ROL::Accumulator: {
    (void)this->read(this->_registers.pc);

    const std::uint8_t old_carry = this->_registers.is_carry_set();
    const std::uint8_t new_carry = this->_registers.a & 0x80;

    this->_registers.a = static_cast<std::uint8_t>((this->_registers.a << 1) | old_carry);

    this->_registers.set_carry(new_carry);
    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::ROL::ZeroPage: {
    break;
  }

  case OpCode::ROL::ZeroPageX: {
    break;
  }

  case OpCode::ROL::Absolute: {
    break;
  }

  case OpCode::ROL::AbsoluteX: {
    break;
  }

  case OpCode::ROR::Accumulator: {
    (void)this->read(this->_registers.pc);

    const std::uint8_t old_carry = this->_registers.is_carry_set();
    const std::uint8_t new_carry = this->_registers.a & 0x01;

    this->_registers.a = static_cast<std::uint8_t>((this->_registers.a >> 1) | (old_carry << 7));

    this->_registers.set_carry(new_carry);
    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::ROR::ZeroPage: {
    break;
  }

  case OpCode::ROR::ZeroPageX: {
    break;
  }

  case OpCode::ROR::Absolute: {
    break;
  }

  case OpCode::ROR::AbsoluteX: {
    break;
  }

  case OpCode::RTI::Implied: {
    (void)this->read(this->_registers.pc);
    (void)this->read(0x0100 | this->_registers.sp++);

    const std::uint8_t p    = this->read(0x0100 | this->_registers.sp++);
    const std::uint8_t low  = this->read(0x0100 | this->_registers.sp++);
    const std::uint8_t high = this->read(0x0100 | this->_registers.sp);

    this->_registers.pc = (high << 8) | low;
    this->_registers.p  = (p & ~0x10) | 0x20;

    break;
  }

  case OpCode::RTS::Implied: {
    (void)this->read(this->_registers.pc);

    (void)this->read(0x0100 | this->_registers.sp++);

    const std::uint8_t low  = this->read(0x0100 | this->_registers.sp++);
    const std::uint8_t high = this->read(0x0100 | this->_registers.sp);

    this->_registers.pc = (high << 8) | low;

    (void)this->read(this->_registers.pc++);

    break;
  }

  case OpCode::SBC::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::SBC::ZeroPage: {
    break;
  }

  case OpCode::SBC::ZeroPageX: {
    break;
  }

  case OpCode::SBC::Absolute: {
    break;
  }

  case OpCode::SBC::AbsoluteX: {
    break;
  }

  case OpCode::SBC::AbsoluteY: {
    break;
  }

  case OpCode::SBC::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();

    const std::uint8_t value = this->read(addr);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::SBC::IndirectIndexed: {
    break;
  }

  case OpCode::SEC::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.set_carry(true);

    break;
  }

  case OpCode::SED::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.set_decimal_mode(true);

    break;
  }

  case OpCode::SEI::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.set_interrupt_disable(true);

    break;
  }

  case OpCode::STA::ZeroPage: {
    const std::uint8_t addr = this->read(this->_registers.pc++);

    this->write(addr, this->_registers.a);

    break;
  }

  case OpCode::STA::ZeroPageX: {
    const std::uint8_t addr = this->read(this->_registers.pc++);

    (void)this->read(addr);

    const std::uint8_t final_addr = static_cast<std::uint8_t>(addr + this->_registers.x);

    this->write(final_addr, this->_registers.a);

    break;
  }

  case OpCode::STA::Absolute: {
    const std::uint8_t low   = this->read(this->_registers.pc++);
    const std::uint8_t high  = this->read(this->_registers.pc++);
    const std::uint16_t addr = (high << 8) | low;

    this->write(addr, this->_registers.a);

    break;
  }

  case OpCode::STA::AbsoluteX: {
    break;
  }

  case OpCode::STA::AbsoluteY: {
    break;
  }

  case OpCode::STA::IndexedIndirect: {
    const std::uint16_t ptr = this->read(this->_registers.pc++);
    (void)this->read(ptr);

    const std::uint8_t indexed_ptr = static_cast<std::uint8_t>(ptr + this->_registers.x);

    const std::uint8_t low  = this->read(indexed_ptr);
    const std::uint8_t high = this->read(static_cast<std::uint8_t>(indexed_ptr + 1));

    const std::uint16_t addr = static_cast<std::uint16_t>((high << 8) | low);

    this->write(addr, this->_registers.a);

    break;
  }

  case OpCode::STA::IndirectIndexed: {
    break;
  }

  case OpCode::STX::ZeroPage: {
    const auto addr = this->read(this->_registers.pc++);
    this->write(addr, this->_registers.x);

    break;
  }

  case OpCode::STX::ZeroPageY: {
    break;
  }

  case OpCode::STX::Absolute: {
    const std::uint8_t low   = this->read(this->_registers.pc++);
    const std::uint8_t high  = this->read(this->_registers.pc++);
    const std::uint16_t addr = (high << 8) | low;

    this->write(addr, this->_registers.x);

    break;
  }

  case OpCode::STY::ZeroPage: {
    const std::uint8_t addr = this->read(this->_registers.pc++);

    this->write(addr, this->_registers.y);

    break;
  }

  case OpCode::STY::ZeroPageX: {
    break;
  }

  case OpCode::STY::Absolute: {
    break;
  }

  case OpCode::TAX::Implied: {
    (void)this->read(this->_registers.pc);

    this->transfer(this->_registers.a, this->_registers.x);

    break;
  }

  case OpCode::TAY::Implied: {
    (void)this->read(this->_registers.pc);

    this->transfer(this->_registers.a, this->_registers.y);

    break;
  }

  case OpCode::TSX::Implied: {
    (void)this->read(this->_registers.pc);

    this->transfer(this->_registers.sp, this->_registers.x);

    break;
  }

  case OpCode::TXA::Implied: {
    (void)this->read(this->_registers.pc);

    this->transfer(this->_registers.x, this->_registers.a);

    break;
  }

  case OpCode::TXS::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.sp = this->_registers.x;

    break;
  }

  case OpCode::TYA::Implied: {
    (void)this->read(this->_registers.pc);

    this->transfer(this->_registers.y, this->_registers.a);

    break;
  }
  }

  return this->_current_cycle_count;
}

void CPU::tick() {
  this->_current_cycle_count++;
  this->_total_cycle_count++;
}

std::uint8_t CPU::read(std::uint16_t addr) {
  // TODO: Replace with bus call when implemented
  const std::uint8_t value = this->_memory[addr];

  this->tick();

  return value;
}

std::uint16_t CPU::resolve_indexed_indirect() {
  const std::uint8_t ptr = this->read(this->_registers.pc++);
  (void)this->read(ptr);

  const std::uint8_t indexed_ptr = static_cast<std::uint8_t>(ptr + this->_registers.x);

  const std::uint8_t low   = this->read(indexed_ptr);
  const std::uint8_t high  = this->read(static_cast<std::uint8_t>(indexed_ptr + 1));
  const std::uint16_t addr = static_cast<std::uint16_t>((high << 8) | low);

  return addr;
}

void CPU::write(std::uint16_t addr, std::uint8_t value) {
  // TODO: Replace with bus call when implemented
  this->_memory[addr] = value;

  this->tick();
}

void CPU::add_with_carry(const std::uint8_t value) {
  const std::uint8_t a = this->_registers.a;

  const std::uint16_t result = a + value + this->_registers.is_carry_set();

  this->_registers.a = static_cast<std::uint8_t>(result);

  this->_registers.set_carry(result > 0xFF);
  this->_registers.set_zero(this->_registers.a == 0);
  this->_registers.set_overflow((a ^ this->_registers.a) & (value ^ this->_registers.a) & 0x80);
  this->_registers.set_negative(this->_registers.a & 0x80);
}

void CPU::bitwise_and(const std::uint8_t value) {
  this->_registers.a &= value;

  this->_registers.set_zero(this->_registers.a == 0);
  this->_registers.set_negative(this->_registers.a & 0x80);
}

void CPU::branch_if(const bool condition) {
  const std::int8_t offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

  if (condition) {
    const std::uint16_t target = static_cast<std::int32_t>(this->_registers.pc) + offset;

    (void)this->read(this->_registers.pc);

    if ((this->_registers.pc & 0xFF00) != (target & 0xFF00)) {
      const std::uint16_t intermediate = (this->_registers.pc & 0xFF00) | (target & 0x00FF);

      (void)this->read(intermediate);

      this->_registers.pc = target;

      return;
    }

    this->_registers.pc = target;

    return;
  }
}

void CPU::compare(const std::uint8_t value) {
  const std::uint8_t result = this->_registers.a - value;

  this->_registers.set_carry(this->_registers.a >= value);
  this->_registers.set_zero(result == 0);
  this->_registers.set_negative(result & 0x80);
}

void CPU::bitwise_eor(const std::uint8_t value) {
  this->_registers.a ^= value;

  this->_registers.set_zero(this->_registers.a == 0);
  this->_registers.set_negative(this->_registers.a & 0x80);
}

void CPU::subtract_with_carry(std::uint8_t value) {
  const std::uint8_t a = this->_registers.a;

  const std::int16_t result = static_cast<std::int16_t>(a) - static_cast<std::int16_t>(value) -
                              !this->_registers.is_carry_set();

  this->_registers.a = static_cast<std::uint8_t>(result);

  this->_registers.set_carry(result >= 0x00);
  this->_registers.set_zero(this->_registers.a == 0);
  this->_registers.set_overflow((a ^ this->_registers.a) & (a ^ value) & 0x80);
  this->_registers.set_negative(this->_registers.a & 0x80);
}

void CPU::transfer(const std::uint8_t value, std::uint8_t& reg) {
  reg = value;

  this->_registers.set_zero(reg == 0);
  this->_registers.set_negative(reg & 0x80);
}
