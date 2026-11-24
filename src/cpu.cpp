#include "cpu.hpp"

#include <ostream>
#include <print>

#include "opcode.hpp"

CPU::CPU(std::array<std::uint8_t, 65536> mem)
    : _registers(), _total_cycle_count{0}, _current_cycle_count{0}, _memory{mem} {}

CPU::~CPU() = default;

std::uint8_t CPU::step() {
  this->_current_cycle_count = 0;

  const auto opcode = this->read(this->_registers.pc++);

  switch (opcode) {

  case OpCode::ADC::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::ZeroPage: {
    const std::uint8_t value = this->read_zero_page();

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::ZeroPageX: {
    const std::uint8_t value = this->read_zero_page_indexed(this->_registers.x);

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::AbsoluteX: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.x);

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::AbsoluteY: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.y);

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::IndexedIndirect: {
    const std::uint8_t value = this->read_indexed_indirect();

    this->add_with_carry(value);

    break;
  }

  case OpCode::ADC::IndirectIndexed: {
    const std::uint8_t value = this->read_indirect_indexed();

    this->add_with_carry(value);

    break;
  }

  case OpCode::AND::Immediate: {
    const uint8_t value = this->read(this->_registers.pc++);

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::ZeroPage: {
    const std::uint8_t value = this->read_zero_page();

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::ZeroPageX: {
    const std::uint8_t value = this->read_zero_page_indexed(this->_registers.x);

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::AbsoluteX: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.x);

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::AbsoluteY: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.y);

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::IndexedIndirect: {
    const std::uint8_t value = this->read_indexed_indirect();

    this->bitwise_and(value);

    break;
  }

  case OpCode::AND::IndirectIndexed: {
    const std::uint8_t value = this->read_indirect_indexed();

    this->bitwise_and(value);

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
    const std::uint8_t addr = this->resolve_zero_page();

    this->shift_left(addr);

    break;
  }

  case OpCode::ASL::ZeroPageX: {
    const std::uint8_t addr = this->resolve_zero_page_indexed(this->_registers.x);

    this->shift_left(addr);

    break;
  }

  case OpCode::ASL::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();

    this->shift_left(addr);

    break;
  }

  case OpCode::ASL::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);

    this->shift_left(addr);

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
    const std::uint8_t value = this->read_zero_page();

    this->bit_test(value);

    break;
  }

  case OpCode::BIT::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->bit_test(value);

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
    (void)this->read(this->_registers.pc++);

    const std::uint8_t pch    = this->_registers.pc >> 8;
    const std::uint8_t pcl    = this->_registers.pc & 0xFF;
    const std::uint8_t status = this->_registers.p | 0x30;

    this->push_stack(pch);
    this->push_stack(pcl);
    this->push_stack(status);

    this->_registers.set_interrupt_disable(true);

    const std::uint8_t low  = this->read(0xFFFE);
    const std::uint8_t high = this->read(0xFFFF);

    this->_registers.pc = (high << 8) | low;

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

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::CMP::ZeroPage: {
    const std::uint8_t value = this->read_zero_page();

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::CMP::ZeroPageX: {
    const std::uint8_t value = this->read_zero_page_indexed(this->_registers.x);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::CMP::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::CMP::AbsoluteX: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.x);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::CMP::AbsoluteY: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.y);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::CMP::IndexedIndirect: {
    const std::uint8_t value = this->read_indexed_indirect();

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::CMP::IndirectIndexed: {
    const std::uint8_t value = this->read_indirect_indexed();

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::CPX::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    this->compare(this->_registers.x, value);

    break;
  }

  case OpCode::CPX::ZeroPage: {
    const std::uint8_t value = this->read_zero_page();

    this->compare(this->_registers.x, value);

    break;
  }

  case OpCode::CPX::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->compare(this->_registers.x, value);

    break;
  }

  case OpCode::CPY::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    this->compare(this->_registers.y, value);

    break;
  }

  case OpCode::CPY::ZeroPage: {
    const std::uint8_t value = this->read_zero_page();

    this->compare(this->_registers.y, value);

    break;
  }

  case OpCode::CPY::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->compare(this->_registers.y, value);

    break;
  }

  case OpCode::DEC::ZeroPage: {
    const std::uint8_t addr = this->resolve_zero_page();

    this->decrement(addr);

    break;
  }

  case OpCode::DEC::ZeroPageX: {
    const std::uint16_t addr = this->resolve_zero_page_indexed(this->_registers.x);

    this->decrement(addr);

    break;
  }

  case OpCode::DEC::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();

    this->decrement(addr);

    break;
  }

  case OpCode::DEC::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);

    this->decrement(addr);

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
    const std::uint8_t value = this->read_zero_page();

    this->bitwise_eor(value);

    break;
  }

  case OpCode::EOR::ZeroPageX: {
    const std::uint8_t value = this->read_zero_page_indexed(this->_registers.x);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::EOR::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->bitwise_eor(value);

    break;
  }

  case OpCode::EOR::AbsoluteX: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.x);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::EOR::AbsoluteY: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.y);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::EOR::IndexedIndirect: {
    const std::uint8_t value = this->read_indexed_indirect();

    this->bitwise_eor(value);

    break;
  }

  case OpCode::EOR::IndirectIndexed: {
    const std::uint8_t value = this->read_indirect_indexed();

    this->bitwise_eor(value);

    break;
  }

  case OpCode::INC::ZeroPage: {
    const std::uint8_t addr = this->resolve_zero_page();

    this->increment(addr);

    break;
  }

  case OpCode::INC::ZeroPageX: {
    const std::uint8_t addr = this->resolve_zero_page_indexed(this->_registers.x);

    this->increment(addr);

    break;
  }

  case OpCode::INC::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();

    this->increment(addr);

    break;
  }

  case OpCode::INC::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);

    this->increment(addr);

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
    const std::uint16_t addr = this->resolve_absolute();

    this->_registers.pc = addr;

    break;
  }

  case OpCode::JMP::Indirect: {
    const std::uint16_t addr = this->resolve_absolute();

    const std::uint8_t target_low  = this->read(addr);
    const std::uint16_t next_addr  = (addr & 0xFF00) | static_cast<std::uint8_t>(addr + 1);
    const std::uint8_t target_high = this->read(next_addr);

    this->_registers.pc = (target_high << 8) | target_low;

    break;
  }

  case OpCode::JSR::Absolute: {
    const std::uint8_t low = this->read(_registers.pc++);
    (void)this->read_stack();

    const std::uint16_t return_addr = this->_registers.pc;

    this->push_stack(static_cast<std::uint8_t>(return_addr >> 8));
    this->push_stack(static_cast<std::uint8_t>(return_addr & 0xFF));

    const auto high = this->read(_registers.pc++);

    this->_registers.pc = static_cast<std::uint16_t>(low | (high << 8));

    break;
  }

  case OpCode::LDA::Immediate: {
    const std::uint8_t value = this->read(_registers.pc++);

    this->assign_register(this->_registers.a, value);

    break;
  }

  case OpCode::LDA::ZeroPage: {
    const std::uint8_t value = this->read_zero_page();

    this->assign_register(this->_registers.a, value);

    break;
  }

  case OpCode::LDA::ZeroPageX: {
    const std::uint8_t value = this->read_zero_page_indexed(this->_registers.x);

    this->assign_register(this->_registers.a, value);

    break;
  }

  case OpCode::LDA::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->assign_register(this->_registers.a, value);

    break;
  }

  case OpCode::LDA::AbsoluteX: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.x);

    this->assign_register(this->_registers.a, value);

    break;
  }

  case OpCode::LDA::AbsoluteY: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.y);

    this->assign_register(this->_registers.a, value);

    break;
  }

  case OpCode::LDA::IndexedIndirect: {
    const std::uint8_t value = this->read_indexed_indirect();

    this->assign_register(this->_registers.a, value);

    break;
  }

  case OpCode::LDA::IndirectIndexed: {
    const std::uint8_t value = this->read_indirect_indexed();

    this->assign_register(this->_registers.a, value);

    break;
  }

  case OpCode::LDX::Immediate: {
    const std::uint8_t value = this->read(_registers.pc++);

    this->assign_register(this->_registers.x, value);

    break;
  }

  case OpCode::LDX::ZeroPage: {
    const std::uint8_t value = this->read_zero_page();

    this->assign_register(this->_registers.x, value);

    break;
  }

  case OpCode::LDX::ZeroPageY: {
    const std::uint8_t value = this->read_zero_page_indexed(this->_registers.y);

    this->assign_register(this->_registers.x, value);

    break;
  }

  case OpCode::LDX::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->assign_register(this->_registers.x, value);

    break;
  }

  case OpCode::LDX::AbsoluteY: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.y);

    this->assign_register(this->_registers.x, value);

    break;
  }

  case OpCode::LDY::Immediate: {
    const std::uint8_t value = this->read(_registers.pc++);

    this->assign_register(this->_registers.y, value);

    break;
  }

  case OpCode::LDY::ZeroPage: {
    const std::uint8_t value = this->read_zero_page();

    this->assign_register(this->_registers.y, value);

    break;
  }

  case OpCode::LDY::ZeroPageX: {
    const std::uint8_t value = this->read_zero_page_indexed(this->_registers.x);

    this->assign_register(this->_registers.y, value);

    break;
  }

  case OpCode::LDY::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->assign_register(this->_registers.y, value);

    break;
  }

  case OpCode::LDY::AbsoluteX: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.x);

    this->assign_register(this->_registers.y, value);

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
    const std::uint8_t addr = this->resolve_zero_page();

    this->shift_right(addr);

    break;
  }

  case OpCode::LSR::ZeroPageX: {
    const std::uint8_t addr = this->resolve_zero_page_indexed(this->_registers.x);

    this->shift_right(addr);

    break;
  }

  case OpCode::LSR::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();

    this->shift_right(addr);

    break;
  }

  case OpCode::LSR::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);

    this->shift_right(addr);

    break;
  }

  case OpCode::NOP::Implied: {
    (void)this->read(this->_registers.pc);

    break;
  }

  case OpCode::ORA::Immediate: {
    const std::uint8_t value = this->read(_registers.pc++);

    this->bitwise_or(value);

    break;
  }

  case OpCode::ORA::ZeroPage: {
    const std::uint8_t value = this->read_zero_page();

    this->bitwise_or(value);

    break;
  }

  case OpCode::ORA::ZeroPageX: {
    const std::uint8_t value = this->read_zero_page_indexed(this->_registers.x);

    this->bitwise_or(value);

    break;
  }

  case OpCode::ORA::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->bitwise_or(value);

    break;
  }

  case OpCode::ORA::AbsoluteX: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.x);

    this->bitwise_or(value);

    break;
  }

  case OpCode::ORA::AbsoluteY: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.y);

    this->bitwise_or(value);

    break;
  }

  case OpCode::ORA::IndexedIndirect: {
    const std::uint8_t value = this->read_indexed_indirect();

    this->bitwise_or(value);

    break;
  }

  case OpCode::ORA::IndirectIndexed: {
    const std::uint8_t value = this->read_indirect_indexed();

    this->bitwise_or(value);

    break;
  }

  case OpCode::PHA::Implied: {
    (void)this->read(this->_registers.pc);

    this->push_stack(this->_registers.a);

    break;
  }

  case OpCode::PHP::Implied: {
    (void)this->read(this->_registers.pc);

    this->push_stack(this->_registers.p | 0x30);

    break;
  }

  case OpCode::PLA::Implied: {
    (void)this->read(this->_registers.pc);
    (void)this->pop_stack();

    this->_registers.a = this->read_stack();

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    break;
  }

  case OpCode::PLP::Implied: {
    (void)this->read(this->_registers.pc);
    (void)this->pop_stack();

    const std::uint8_t value = this->read_stack();

    this->_registers.p = (value & ~0x10) | 0x20;

    break;
  }

  case OpCode::ROL::Accumulator: {
    (void)this->read(this->_registers.pc);

    const std::uint8_t old_carry = this->_registers.is_carry_set();
    const std::uint8_t new_carry = this->_registers.a & 0x80;

    const std::uint8_t result = (this->_registers.a << 1) | old_carry;

    this->_registers.a = result;

    this->_registers.set_carry(new_carry);
    this->_registers.set_zero(result == 0);
    this->_registers.set_negative(result & 0x80);

    break;
  }

  case OpCode::ROL::ZeroPage: {
    const std::uint8_t addr = this->resolve_zero_page();

    this->rotate_left(addr);

    break;
  }

  case OpCode::ROL::ZeroPageX: {
    const std::uint8_t addr = this->resolve_zero_page_indexed(this->_registers.x);

    this->rotate_left(addr);

    break;
  }

  case OpCode::ROL::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();

    this->rotate_left(addr);

    break;
  }

  case OpCode::ROL::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);

    this->rotate_left(addr);

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
    const std::uint8_t addr = this->resolve_zero_page();

    this->rotate_right(addr);

    break;
  }

  case OpCode::ROR::ZeroPageX: {
    const std::uint8_t addr = this->resolve_zero_page_indexed(this->_registers.x);

    this->rotate_right(addr);

    break;
  }

  case OpCode::ROR::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();

    this->rotate_right(addr);

    break;
  }

  case OpCode::ROR::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);

    this->rotate_right(addr);

    break;
  }

  case OpCode::RTI::Implied: {
    (void)this->read(this->_registers.pc);
    (void)this->pop_stack();

    const std::uint8_t p    = this->pop_stack();
    const std::uint8_t low  = this->pop_stack();
    const std::uint8_t high = this->read_stack();

    this->_registers.pc = (high << 8) | low;
    this->_registers.p  = (p & ~0x10) | 0x20;

    break;
  }

  case OpCode::RTS::Implied: {
    (void)this->read(this->_registers.pc);

    (void)this->pop_stack();

    const std::uint8_t low  = this->pop_stack();
    const std::uint8_t high = this->read_stack();

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
    const std::uint8_t value = this->read_zero_page();

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::SBC::ZeroPageX: {
    const std::uint8_t value = this->read_zero_page_indexed(this->_registers.x);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::SBC::Absolute: {
    const std::uint8_t value = this->read_absolute();

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::SBC::AbsoluteX: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.x);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::SBC::AbsoluteY: {
    const std::uint8_t value = this->read_absolute_indexed(this->_registers.y);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::SBC::IndexedIndirect: {
    const std::uint8_t value = this->read_indexed_indirect();

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::SBC::IndirectIndexed: {
    const std::uint8_t value = this->read_indirect_indexed();

    this->subtract_with_carry(value);

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

    const auto final_addr = static_cast<std::uint8_t>(addr + this->_registers.x);

    this->write(final_addr, this->_registers.a);

    break;
  }

  case OpCode::STA::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();

    this->write(addr, this->_registers.a);

    break;
  }

  case OpCode::STA::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);

    this->write(addr, this->_registers.a);

    break;
  }

  case OpCode::STA::AbsoluteY: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.y);

    this->write(addr, this->_registers.a);

    break;
  }

  case OpCode::STA::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();

    this->write(addr, this->_registers.a);

    break;
  }

  case OpCode::STA::IndirectIndexed: {
    const std::uint16_t addr = this->resolve_indirect_indexed();

    this->write(addr, this->_registers.a);

    break;
  }

  case OpCode::STX::ZeroPage: {
    const std::uint8_t addr = this->read(this->_registers.pc++);

    this->write(addr, this->_registers.x);

    break;
  }

  case OpCode::STX::ZeroPageY: {
    const std::uint16_t addr = this->resolve_zero_page_indexed(this->_registers.y);

    this->write(addr, this->_registers.x);

    break;
  }

  case OpCode::STX::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();

    this->write(addr, this->_registers.x);

    break;
  }

  case OpCode::STY::ZeroPage: {
    const std::uint8_t addr = this->read(this->_registers.pc++);

    this->write(addr, this->_registers.y);

    break;
  }

  case OpCode::STY::ZeroPageX: {
    const std::uint16_t addr = this->resolve_zero_page_indexed(this->_registers.x);

    this->write(addr, this->_registers.y);

    break;
  }

  case OpCode::STY::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();

    this->write(addr, this->_registers.y);

    break;
  }

  case OpCode::TAX::Implied: {
    (void)this->read(this->_registers.pc);

    this->assign_register(this->_registers.x, this->_registers.a);

    break;
  }

  case OpCode::TAY::Implied: {
    (void)this->read(this->_registers.pc);

    this->assign_register(this->_registers.y, this->_registers.a);

    break;
  }

  case OpCode::TSX::Implied: {
    (void)this->read(this->_registers.pc);

    this->assign_register(this->_registers.x, this->_registers.sp);

    break;
  }

  case OpCode::TXA::Implied: {
    (void)this->read(this->_registers.pc);

    this->assign_register(this->_registers.a, this->_registers.x);

    break;
  }

  case OpCode::TXS::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.sp = this->_registers.x;

    break;
  }

  case OpCode::TYA::Implied: {
    (void)this->read(this->_registers.pc);

    this->assign_register(this->_registers.a, this->_registers.y);

    break;
  }

  case OpCode::Unofficial::DCP::ZeroPage: {
    const std::uint16_t addr = this->resolve_zero_page();
    const std::uint8_t value = this->decrement(addr);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::Unofficial::DCP::ZeroPageX: {
    const std::uint16_t addr = this->resolve_zero_page_indexed(this->_registers.x);
    const std::uint8_t value = this->decrement(addr);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::Unofficial::DCP::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();
    const std::uint8_t value = this->decrement(addr);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::Unofficial::DCP::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);
    const std::uint8_t value = this->decrement(addr);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::Unofficial::DCP::AbsoluteY: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.y);
    const std::uint8_t value = this->decrement(addr);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::Unofficial::DCP::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();
    const std::uint8_t value = this->decrement(addr);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::Unofficial::DCP::IndirectIndexed: {
    const std::uint16_t addr = this->resolve_indirect_indexed();
    const std::uint8_t value = this->decrement(addr);

    this->compare(this->_registers.a, value);

    break;
  }

  case OpCode::Unofficial::ISC::ZeroPage: {
    const std::uint16_t addr = this->resolve_zero_page();
    const std::uint8_t value = this->increment(addr);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::Unofficial::ISC::ZeroPageX: {
    const std::uint16_t addr = this->resolve_zero_page_indexed(this->_registers.x);
    const std::uint8_t value = this->increment(addr);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::Unofficial::ISC::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();
    const std::uint8_t value = this->increment(addr);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::Unofficial::ISC::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);
    const std::uint8_t value = this->increment(addr);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::Unofficial::ISC::AbsoluteY: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.y);
    const std::uint8_t value = this->increment(addr);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::Unofficial::ISC::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();
    const std::uint8_t value = this->increment(addr);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::Unofficial::ISC::IndirectIndexed: {
    const std::uint16_t addr = this->resolve_indirect_indexed();
    const std::uint8_t value = this->increment(addr);

    this->subtract_with_carry(value);

    break;
  }

  case OpCode::Unofficial::NOP::ZeroPage1:
  case OpCode::Unofficial::NOP::ZeroPage2:
  case OpCode::Unofficial::NOP::ZeroPage3: {
    (void)this->read_zero_page();

    break;
  }

  case OpCode::Unofficial::NOP::Absolute: {
    (void)this->read_absolute();

    break;
  }

  case OpCode::Unofficial::NOP::ZeroPageX1:
  case OpCode::Unofficial::NOP::ZeroPageX2:
  case OpCode::Unofficial::NOP::ZeroPageX3:
  case OpCode::Unofficial::NOP::ZeroPageX4:
  case OpCode::Unofficial::NOP::ZeroPageX5:
  case OpCode::Unofficial::NOP::ZeroPageX6: {
    (void)this->read_zero_page_indexed(this->_registers.x);

    break;
  }

  case OpCode::Unofficial::NOP::Implied1:
  case OpCode::Unofficial::NOP::Implied2:
  case OpCode::Unofficial::NOP::Implied3:
  case OpCode::Unofficial::NOP::Implied4:
  case OpCode::Unofficial::NOP::Implied5:
  case OpCode::Unofficial::NOP::Implied6: {
    (void)this->read(this->_registers.pc);

    break;
  }

  case OpCode::Unofficial::NOP::Immediate1:
  case OpCode::Unofficial::NOP::Immediate2:
  case OpCode::Unofficial::NOP::Immediate3:
  case OpCode::Unofficial::NOP::Immediate4:
  case OpCode::Unofficial::NOP::Immediate5: {
    (void)this->read(this->_registers.pc++);

    break;
  }

  case OpCode::Unofficial::NOP::AbsoluteX1:
  case OpCode::Unofficial::NOP::AbsoluteX2:
  case OpCode::Unofficial::NOP::AbsoluteX3:
  case OpCode::Unofficial::NOP::AbsoluteX4:
  case OpCode::Unofficial::NOP::AbsoluteX5:
  case OpCode::Unofficial::NOP::AbsoluteX6: {
    (void)this->read_absolute_indexed(this->_registers.x);

    break;
  }

  case OpCode::Unofficial::RLA::ZeroPage: {
    const std::uint16_t addr = this->resolve_zero_page();
    const std::uint8_t value = this->rotate_left(addr);

    this->bitwise_and(value);

    break;
  }

  case OpCode::Unofficial::RLA::ZeroPageX: {
    const std::uint16_t addr = this->resolve_zero_page_indexed(this->_registers.x);
    const std::uint8_t value = this->rotate_left(addr);

    this->bitwise_and(value);

    break;
  }

  case OpCode::Unofficial::RLA::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();
    const std::uint8_t value = this->rotate_left(addr);

    this->bitwise_and(value);

    break;
  }

  case OpCode::Unofficial::RLA::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);
    const std::uint8_t value = this->rotate_left(addr);

    this->bitwise_and(value);

    break;
  }

  case OpCode::Unofficial::RLA::AbsoluteY: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.y);
    const std::uint8_t value = this->rotate_left(addr);

    this->bitwise_and(value);

    break;
  }

  case OpCode::Unofficial::RLA::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();
    const std::uint8_t value = this->rotate_left(addr);

    this->bitwise_and(value);

    break;
  }

  case OpCode::Unofficial::RLA::IndirectIndexed: {
    const std::uint16_t addr = this->resolve_indirect_indexed();
    const std::uint8_t value = this->rotate_left(addr);

    this->bitwise_and(value);

    break;
  }

  case OpCode::Unofficial::RRA::ZeroPage: {
    const std::uint16_t addr = this->resolve_zero_page();
    const std::uint8_t value = this->rotate_right(addr);

    this->add_with_carry(value);

    break;
  }

  case OpCode::Unofficial::RRA::ZeroPageX: {
    const std::uint16_t addr = this->resolve_zero_page_indexed(this->_registers.x);
    const std::uint8_t value = this->rotate_right(addr);

    this->add_with_carry(value);

    break;
  }

  case OpCode::Unofficial::RRA::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();
    const std::uint8_t value = this->rotate_right(addr);

    this->add_with_carry(value);

    break;
  }

  case OpCode::Unofficial::RRA::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);
    const std::uint8_t value = this->rotate_right(addr);

    this->add_with_carry(value);

    break;
  }

  case OpCode::Unofficial::RRA::AbsoluteY: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.y);
    const std::uint8_t value = this->rotate_right(addr);

    this->add_with_carry(value);

    break;
  }

  case OpCode::Unofficial::RRA::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();
    const std::uint8_t value = this->rotate_right(addr);

    this->add_with_carry(value);

    break;
  }

  case OpCode::Unofficial::RRA::IndirectIndexed: {
    const std::uint16_t addr = this->resolve_indirect_indexed();
    const std::uint8_t value = this->rotate_right(addr);

    this->add_with_carry(value);

    break;
  }

  case OpCode::Unofficial::SLO::ZeroPage: {
    const std::uint16_t addr = this->resolve_zero_page();
    const std::uint8_t value = this->shift_left(addr);

    this->bitwise_or(value);

    break;
  }

  case OpCode::Unofficial::SLO::ZeroPageX: {
    const std::uint16_t addr = this->resolve_zero_page_indexed(this->_registers.x);
    const std::uint8_t value = this->shift_left(addr);

    this->bitwise_or(value);

    break;
  }

  case OpCode::Unofficial::SLO::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();
    const std::uint8_t value = this->shift_left(addr);

    this->bitwise_or(value);

    break;
  }

  case OpCode::Unofficial::SLO::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);
    const std::uint8_t value = this->shift_left(addr);

    this->bitwise_or(value);

    break;
  }

  case OpCode::Unofficial::SLO::AbsoluteY: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.y);
    const std::uint8_t value = this->shift_left(addr);

    this->bitwise_or(value);

    break;
  }

  case OpCode::Unofficial::SLO::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();
    const std::uint8_t value = this->shift_left(addr);

    this->bitwise_or(value);

    break;
  }

  case OpCode::Unofficial::SLO::IndirectIndexed: {
    const std::uint16_t addr = this->resolve_indirect_indexed();
    const std::uint8_t value = this->shift_left(addr);

    this->bitwise_or(value);

    break;
  }

  case OpCode::Unofficial::SRE::ZeroPage: {
    const std::uint16_t addr = this->resolve_zero_page();
    const std::uint8_t value = this->shift_right(addr);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::Unofficial::SRE::ZeroPageX: {
    const std::uint16_t addr = this->resolve_zero_page_indexed(this->_registers.x);
    const std::uint8_t value = this->shift_right(addr);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::Unofficial::SRE::Absolute: {
    const std::uint16_t addr = this->resolve_absolute();
    const std::uint8_t value = this->shift_right(addr);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::Unofficial::SRE::AbsoluteX: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.x);
    const std::uint8_t value = this->shift_right(addr);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::Unofficial::SRE::AbsoluteY: {
    const std::uint16_t addr = this->resolve_absolute_indexed(this->_registers.y);
    const std::uint8_t value = this->shift_right(addr);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::Unofficial::SRE::IndexedIndirect: {
    const std::uint16_t addr = this->resolve_indexed_indirect();
    const std::uint8_t value = this->shift_right(addr);

    this->bitwise_eor(value);

    break;
  }

  case OpCode::Unofficial::SRE::IndirectIndexed: {
    const std::uint16_t addr = this->resolve_indirect_indexed();
    const std::uint8_t value = this->shift_right(addr);

    this->bitwise_eor(value);

    break;
  }
  }

  return this->_current_cycle_count;
}

void CPU::set_test_state(const Registers& registers,
                         std::array<std::uint8_t, 65536>& memory,
                         const std::uint64_t total_cycle_count) {
  this->_registers           = registers;
  this->_memory              = memory;
  this->_current_cycle_count = 0;
  this->_total_cycle_count   = total_cycle_count;
}

void CPU::tick() {
  this->_current_cycle_count++;
  this->_total_cycle_count++;
}

std::uint8_t CPU::read(const std::uint16_t addr) {
  // TODO: Replace with bus call when implemented
  const std::uint8_t value = this->_memory[addr];

  this->tick();

  return value;
}

void CPU::write(const std::uint16_t addr, const std::uint8_t value) {
  // TODO: Replace with bus call when implemented
  this->_memory[addr] = value;

  this->tick();
}

std::uint8_t CPU::read_stack() {
  const std::uint8_t value = this->read(0x0100 | this->_registers.sp);

  return value;
}

std::uint8_t CPU::pop_stack() {
  const std::uint8_t value = this->read(0x0100 | this->_registers.sp++);

  return value;
}

void CPU::push_stack(const std::uint8_t value) { this->write(0x0100 | this->_registers.sp--, value); }

std::uint8_t CPU::read_zero_page() {
  const std::uint8_t addr  = this->resolve_zero_page();
  const std::uint8_t value = this->read(addr);

  return value;
}

std::uint16_t CPU::resolve_zero_page() {
  const std::uint8_t addr = this->read(this->_registers.pc++);

  return addr;
}

std::uint8_t CPU::read_zero_page_indexed(std::uint8_t index) {
  const std::uint16_t addr = this->resolve_zero_page_indexed(index);
  const std::uint8_t value = this->read(addr);

  return value;
}

std::uint16_t CPU::resolve_zero_page_indexed(std::uint8_t index) {
  const std::uint8_t addr = this->read(this->_registers.pc++);

  const std::uint8_t indexed_addr = addr + index;

  (void)this->read(addr);

  return indexed_addr;
}

std::uint8_t CPU::read_absolute() {
  const std::uint16_t addr = this->resolve_absolute();
  const std::uint8_t value = this->read(addr);

  return value;
}

std::uint16_t CPU::resolve_absolute() {
  const std::uint8_t low   = this->read(this->_registers.pc++);
  const std::uint8_t high  = this->read(this->_registers.pc++);
  const std::uint16_t addr = (high << 8) | low;

  return addr;
}

std::uint8_t CPU::read_absolute_indexed(const std::uint8_t index) {
  const std::uint8_t low  = this->read(this->_registers.pc++);
  const std::uint8_t high = this->read(this->_registers.pc++);

  const std::uint16_t indexed_low = low + index;

  const std::uint16_t addr = (high << 8) | static_cast<std::uint8_t>(indexed_low);

  std::uint8_t value = this->read(addr);

  if (indexed_low > 0xFF) {
    const auto fixed_high          = static_cast<std::uint8_t>(high + 1);
    const std::uint16_t fixed_addr = (fixed_high << 8) | static_cast<std::uint8_t>(indexed_low);

    value = this->read(fixed_addr);
  }

  return value;
}

std::uint16_t CPU::resolve_absolute_indexed(const std::uint8_t index) {
  const std::uint8_t low  = this->read(this->_registers.pc++);
  const std::uint8_t high = this->read(this->_registers.pc++);

  const std::uint16_t indexed_low = low + index;

  std::uint16_t addr = (high << 8) | static_cast<std::uint8_t>(indexed_low);

  (void)this->read(addr);

  if (indexed_low > 0xFF) {
    const auto fixed_high = static_cast<std::uint8_t>(high + 1);

    addr = (fixed_high << 8) | static_cast<std::uint8_t>(indexed_low);
  }

  return addr;
}

std::uint8_t CPU::read_indexed_indirect() {
  const std::uint16_t addr = this->resolve_indexed_indirect();
  const std::uint8_t value = this->read(addr);

  return value;
}

std::uint16_t CPU::resolve_indexed_indirect() {
  const std::uint8_t ptr = this->read(this->_registers.pc++);

  (void)this->read(ptr);

  const auto indexed_ptr = static_cast<std::uint8_t>(ptr + this->_registers.x);

  const std::uint8_t low  = this->read(indexed_ptr);
  const std::uint8_t high = this->read(static_cast<std::uint8_t>(indexed_ptr + 1));
  const auto addr         = static_cast<std::uint16_t>((high << 8) | low);

  return addr;
}

std::uint8_t CPU::read_indirect_indexed() {
  const std::uint8_t ptr  = this->read(this->_registers.pc++);
  const std::uint8_t low  = this->read(ptr);
  const std::uint8_t high = this->read(static_cast<std::uint8_t>(ptr + 1));

  const std::uint16_t indexed_low = low + this->_registers.y;
  const std::uint16_t addr        = (high << 8) | static_cast<std::uint8_t>(indexed_low);

  std::uint8_t value = this->read(addr);

  if (indexed_low > 0xFF) {
    const std::uint8_t fixed_high  = high + 1;
    const std::uint16_t fixed_addr = (fixed_high << 8) | static_cast<std::uint8_t>(indexed_low);

    value = this->read(fixed_addr);
  }

  return value;
}

std::uint16_t CPU::resolve_indirect_indexed() {
  const std::uint8_t ptr  = this->read(this->_registers.pc++);
  const std::uint8_t low  = this->read(ptr);
  const std::uint8_t high = this->read(static_cast<std::uint8_t>(ptr + 1));

  const std::uint16_t indexed_low = low + this->_registers.y;

  std::uint16_t addr = (high << 8) | static_cast<std::uint8_t>(indexed_low);

  (void)this->read(addr);

  if (indexed_low > 0xFF) {
    const std::uint8_t fixed_high = high + 1;

    addr = (fixed_high << 8) | static_cast<std::uint8_t>(indexed_low);
  }

  return addr;
}

void CPU::bitwise_and(const std::uint8_t value) {
  this->_registers.a &= value;

  this->_registers.set_zero(this->_registers.a == 0);
  this->_registers.set_negative(this->_registers.a & 0x80);
}

void CPU::bitwise_or(const std::uint8_t value) {
  this->_registers.a |= value;

  this->_registers.set_zero(this->_registers.a == 0);
  this->_registers.set_negative(this->_registers.a & 0x80);
}

void CPU::bitwise_eor(const std::uint8_t value) {
  this->_registers.a ^= value;

  this->_registers.set_zero(this->_registers.a == 0);
  this->_registers.set_negative(this->_registers.a & 0x80);
}

std::uint8_t CPU::shift_left(const std::uint16_t addr) {
  const std::uint8_t value  = this->read(addr);
  const std::uint8_t result = value << 1;

  this->write(addr, value);
  this->write(addr, result);

  this->_registers.set_carry(value & 0x80);
  this->_registers.set_zero(result == 0);
  this->_registers.set_negative(result & 0x80);

  return result;
}

std::uint8_t CPU::shift_right(const std::uint16_t addr) {
  const std::uint8_t value  = this->read(addr);
  const std::uint8_t carry  = value & 0x01;
  const std::uint8_t result = value >> 1;

  this->write(addr, value);
  this->write(addr, result);

  this->_registers.set_carry(carry);
  this->_registers.set_zero(result == 0);
  this->_registers.set_negative(false);

  return result;
}

std::uint8_t CPU::rotate_left(std::uint16_t addr) {
  const std::uint8_t value = this->read(addr);

  const std::uint8_t old_carry = this->_registers.is_carry_set();
  const std::uint8_t new_carry = value & 0x80;

  const auto result = static_cast<std::uint8_t>((value << 1) | old_carry);

  this->write(addr, value);
  this->write(addr, result);

  this->_registers.set_carry(new_carry);
  this->_registers.set_zero(result == 0);
  this->_registers.set_negative(result & 0x80);

  return result;
}

std::uint8_t CPU::rotate_right(const std::uint16_t addr) {
  const std::uint8_t value = this->read(addr);

  const std::uint8_t old_carry = this->_registers.is_carry_set();
  const std::uint8_t new_carry = value & 0x01;

  const auto result = static_cast<std::uint8_t>((value >> 1) | (old_carry << 7));

  this->write(addr, value);
  this->write(addr, result);

  this->_registers.set_carry(new_carry);
  this->_registers.set_zero(result == 0);
  this->_registers.set_negative(result & 0x80);

  return result;
}

void CPU::branch_if(const bool condition) {
  const auto offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

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

void CPU::bit_test(const std::uint8_t value) {
  const std::uint8_t result = this->_registers.a & value;

  this->_registers.set_zero(result == 0);
  this->_registers.set_overflow(value & 0x40);
  this->_registers.set_negative(value & 0x80);
}

void CPU::compare(const std::uint8_t reg, const std::uint8_t value) {
  const std::uint8_t result = reg - value;

  this->_registers.set_carry(reg >= value);
  this->_registers.set_zero(result == 0);
  this->_registers.set_negative(result & 0x80);
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

void CPU::subtract_with_carry(const std::uint8_t value) {
  const std::uint8_t a = this->_registers.a;

  const auto result = static_cast<std::int16_t>(a) - static_cast<std::int16_t>(value) -
                      !(this->_registers.is_carry_set());

  this->_registers.a = static_cast<std::uint8_t>(result);

  this->_registers.set_carry(result >= 0x00);
  this->_registers.set_zero(this->_registers.a == 0);
  this->_registers.set_overflow((a ^ this->_registers.a) & (a ^ value) & 0x80);
  this->_registers.set_negative(this->_registers.a & 0x80);
}

std::uint8_t CPU::increment(const std::uint16_t addr) {
  const std::uint8_t value  = this->read(addr);
  const std::uint8_t result = value + 1;

  this->write(addr, value);
  this->write(addr, result);

  this->_registers.set_zero(result == 0);
  this->_registers.set_negative(result & 0x80);

  return result;
}

std::uint8_t CPU::decrement(const std::uint16_t addr) {
  const std::uint8_t value  = this->read(addr);
  const std::uint8_t result = value - 1;

  this->write(addr, value);
  this->write(addr, result);

  this->_registers.set_zero(result == 0);
  this->_registers.set_negative(result & 0x80);

  return result;
}

void CPU::assign_register(std::uint8_t& reg, const std::uint8_t value) {
  reg = value;

  this->_registers.set_zero(reg == 0);
  this->_registers.set_negative(reg & 0x80);
}
