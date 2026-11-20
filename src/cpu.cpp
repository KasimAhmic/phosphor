#include "cpu.hpp"
#include <ostream>
#include <print>
#include "opcode.hpp"

#define RETURN_CYCLE_COUNT(count)                                                                                      \
  do {                                                                                                                 \
    this->_cycle_count += (count);                                                                                     \
    return (count);                                                                                                    \
  } while (0)

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
    const std::uint8_t value = this->read(this->_registers.pc++);
    const std::uint8_t a     = this->_registers.a;

    const std::uint16_t result = a + value + this->_registers.is_carry_set();

    this->_registers.a = static_cast<std::uint8_t>(result);

    this->_registers.set_carry(result > 0xFF);
    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_overflow((this->_registers.a ^ a) & (this->_registers.a ^ value) & 0x80);
    this->_registers.set_negative(this->_registers.a & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::ADC::ZeroPage: {
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
    break;
  }

  case OpCode::ADC::IndirectIndexed: {
    break;
  }

  case OpCode::AND::Immediate: {
    const uint8_t value = this->read(this->_registers.pc++);

    this->_registers.a &= value;

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::AND::ZeroPage: {
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
    break;
  }

  case OpCode::AND::IndirectIndexed: {
    break;
  }

  case OpCode::ASL::Accumulator: {
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
    const std::int8_t offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

    if (this->_registers.is_carry_clear()) {
      const std::uint16_t target = static_cast<std::int32_t>(this->_registers.pc) + offset;

      (void)this->read(this->_registers.pc);

      if ((this->_registers.pc & 0xFF00) != (target & 0xFF00)) {
        const std::uint16_t intermediate = (this->_registers.pc & 0xFF00) | (target & 0x00FF);

        (void)this->read(intermediate);

        this->_registers.pc = intermediate;

        RETURN_CYCLE_COUNT(4);
      }

      this->_registers.pc = target;

      RETURN_CYCLE_COUNT(3);
    }

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::BCS::Relative: {
    const std::int8_t offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

    if (this->_registers.is_carry_set()) {
      const std::uint16_t target = static_cast<std::int32_t>(this->_registers.pc) + offset;

      (void)this->read(this->_registers.pc);

      if ((this->_registers.pc & 0xFF00) != (target & 0xFF00)) {
        const std::uint16_t intermediate = (this->_registers.pc & 0xFF00) | (target & 0x00FF);

        (void)this->read(intermediate);

        this->_registers.pc = intermediate;

        RETURN_CYCLE_COUNT(4);
      }

      this->_registers.pc = target;

      RETURN_CYCLE_COUNT(3);
    }

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::BEQ::Relative: {
    const std::int8_t offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

    if (this->_registers.is_zero_set()) {
      const std::uint16_t target = static_cast<std::int32_t>(this->_registers.pc) + offset;

      (void)this->read(this->_registers.pc);

      if ((this->_registers.pc & 0xFF00) != (target & 0xFF00)) {
        const std::uint16_t intermediate = (this->_registers.pc & 0xFF00) | (target & 0x00FF);

        (void)this->read(intermediate);

        this->_registers.pc = intermediate;

        RETURN_CYCLE_COUNT(4);
      }

      this->_registers.pc = target;

      RETURN_CYCLE_COUNT(3);
    }

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::BIT::ZeroPage: {
    const std::uint8_t addr  = this->read(this->_registers.pc++);
    const std::uint8_t value = this->read(addr);

    const std::uint8_t result = this->_registers.a & value;

    this->_registers.set_zero(result == 0);
    this->_registers.set_overflow(value & 0x40);
    this->_registers.set_negative(value & 0x80);

    RETURN_CYCLE_COUNT(3);
  }

  case OpCode::BIT::Absolute: {
    break;
  }

  case OpCode::BMI::Relative: {
    const std::int8_t offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

    if (this->_registers.is_negative_set()) {
      const std::uint16_t target = static_cast<std::int32_t>(this->_registers.pc) + offset;

      (void)this->read(this->_registers.pc);

      if ((this->_registers.pc & 0xFF00) != (target & 0xFF00)) {
        const std::uint16_t intermediate = (this->_registers.pc & 0xFF00) | (target & 0x00FF);

        (void)this->read(intermediate);

        this->_registers.pc = intermediate;

        RETURN_CYCLE_COUNT(4);
      }

      this->_registers.pc = target;

      RETURN_CYCLE_COUNT(3);
    }

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::BNE::Relative: {
    const std::int8_t offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

    if (this->_registers.is_zero_clear()) {
      const std::uint16_t target = static_cast<std::int32_t>(this->_registers.pc) + offset;

      (void)this->read(this->_registers.pc);

      if ((this->_registers.pc & 0xFF00) != (target & 0xFF00)) {
        const std::uint16_t intermediate = (this->_registers.pc & 0xFF00) | (target & 0x00FF);

        (void)this->read(intermediate);

        this->_registers.pc = intermediate;

        RETURN_CYCLE_COUNT(4);
      }

      this->_registers.pc = target;

      RETURN_CYCLE_COUNT(3);
    }

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::BPL::Relative: {
    const std::int8_t offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

    if (this->_registers.is_negative_clear()) {
      const std::uint16_t target = static_cast<std::int32_t>(this->_registers.pc) + offset;

      (void)this->read(this->_registers.pc);

      if ((this->_registers.pc & 0xFF00) != (target & 0xFF00)) {
        const std::uint16_t intermediate = (this->_registers.pc & 0xFF00) | (target & 0x00FF);

        (void)this->read(intermediate);

        this->_registers.pc = intermediate;

        RETURN_CYCLE_COUNT(4);
      }

      this->_registers.pc = target;

      RETURN_CYCLE_COUNT(3);
    }

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::BRK::Implied: {
    break;
  }

  case OpCode::BVC::Relative: {
    const std::int8_t offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

    if (this->_registers.is_overflow_clear()) {
      const std::uint16_t target = static_cast<std::int32_t>(this->_registers.pc) + offset;

      (void)this->read(this->_registers.pc);

      if ((this->_registers.pc & 0xFF00) != (target & 0xFF00)) {
        const std::uint16_t intermediate = (this->_registers.pc & 0xFF00) | (target & 0x00FF);

        (void)this->read(intermediate);

        this->_registers.pc = intermediate;

        RETURN_CYCLE_COUNT(4);
      }

      this->_registers.pc = target;

      RETURN_CYCLE_COUNT(3);
    }

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::BVS::Relative: {
    const std::int8_t offset = static_cast<std::int8_t>(this->read(this->_registers.pc++));

    if (this->_registers.is_overflow_set()) {
      const std::uint16_t target = static_cast<std::int32_t>(this->_registers.pc) + offset;

      (void)this->read(this->_registers.pc);

      if ((this->_registers.pc & 0xFF00) != (target & 0xFF00)) {
        const std::uint16_t intermediate = (this->_registers.pc & 0xFF00) | (target & 0x00FF);

        (void)this->read(intermediate);

        this->_registers.pc = intermediate;

        RETURN_CYCLE_COUNT(4);
      }

      this->_registers.pc = target;

      RETURN_CYCLE_COUNT(3);
    }

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::CLC::Implied: {
    this->_registers.set_carry(false);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::CLD::Implied: {
    this->_registers.set_decimal_mode(false);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::CLI::Implied: {
    this->_registers.set_interrupt_disable(false);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::CLV::Implied: {
    this->_registers.set_overflow(false);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::CMP::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    const std::uint8_t result = this->_registers.a - value;

    this->_registers.set_carry(this->_registers.a >= value);
    this->_registers.set_zero(result == 0);
    this->_registers.set_negative(result & 0x80);

    RETURN_CYCLE_COUNT(2);
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

    RETURN_CYCLE_COUNT(2);
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

    RETURN_CYCLE_COUNT(2);
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

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::DEY::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.y--;

    this->_registers.set_zero(this->_registers.y == 0);
    this->_registers.set_negative(this->_registers.y & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::EOR::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);

    this->_registers.a ^= value;

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::EOR::ZeroPage: {
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

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::INY::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.y++;

    this->_registers.set_zero(this->_registers.y == 0);
    this->_registers.set_negative(this->_registers.y & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::JMP::Absolute: {
    const auto low  = this->read(_registers.pc++);
    const auto high = this->read(_registers.pc++);

    this->_registers.pc = static_cast<std::uint16_t>(low | (high << 8));

    RETURN_CYCLE_COUNT(3);
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

    RETURN_CYCLE_COUNT(6);
  }

  case OpCode::LDA::Immediate: {
    this->_registers.a = this->read(_registers.pc++);

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative((this->_registers.a & 0x80) != 0);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::LDA::ZeroPage: {
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

    RETURN_CYCLE_COUNT(4);
  }

  case OpCode::LDA::AbsoluteX: {
    break;
  }

  case OpCode::LDA::AbsoluteY: {
    break;
  }

  case OpCode::LDA::IndexedIndirect: {
    break;
  }

  case OpCode::LDA::IndirectIndexed: {
    break;
  }

  case OpCode::LDX::Immediate: {
    this->_registers.x = this->read(_registers.pc++);

    this->_registers.set_zero(this->_registers.x == 0);
    this->_registers.set_negative(this->_registers.x & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::LDX::ZeroPage: {
    break;
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

    RETURN_CYCLE_COUNT(4);
  }

  case OpCode::LDX::AbsoluteY: {
    break;
  }

  case OpCode::LDY::Immediate: {
    this->_registers.y = this->read(_registers.pc++);

    this->_registers.set_zero(this->_registers.y == 0);
    this->_registers.set_negative(this->_registers.y & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::LDY::ZeroPage: {
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
    this->_cycle_count += 2;

    return 2;
  }

  case OpCode::ORA::Immediate: {
    const std::uint8_t value = this->read(_registers.pc++);

    this->_registers.a |= value;

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::ORA::ZeroPage: {
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
    break;
  }

  case OpCode::ORA::IndirectIndexed: {
    break;
  }

  case OpCode::PHA::Implied: {
    (void)this->read(this->_registers.pc);

    this->write(0x0100 | this->_registers.sp--, this->_registers.a);

    RETURN_CYCLE_COUNT(3);
  }

  case OpCode::PHP::Implied: {
    (void)this->read(this->_registers.pc);

    this->write(0x0100 | this->_registers.sp--, this->_registers.p | 0x30);

    RETURN_CYCLE_COUNT(3);
  }

  case OpCode::PLA::Implied: {
    (void)this->read(this->_registers.pc);
    (void)this->read(0x0100 | this->_registers.sp++);

    this->_registers.a = this->read(0x0100 | this->_registers.sp);

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    RETURN_CYCLE_COUNT(4);
  }

  case OpCode::PLP::Implied: {
    (void)this->read(this->_registers.pc);
    (void)this->read(0x0100 | this->_registers.sp++);

    this->_registers.p = (this->read(0x0100 | this->_registers.sp) & ~0x10) | 0x20;

    RETURN_CYCLE_COUNT(4);
  }

  case OpCode::ROL::Accumulator: {
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

    this->_registers.set_carry(p & 0x01);
    this->_registers.set_zero(p & 0x02);
    this->_registers.set_interrupt_disable(p & 0x04);
    this->_registers.set_decimal_mode(p & 0x08);
    this->_registers.set_overflow(p & 0x40);
    this->_registers.set_negative(p & 0x80);

    RETURN_CYCLE_COUNT(6);
  }

  case OpCode::RTS::Implied: {
    (void)this->read(this->_registers.pc);

    (void)this->read(0x0100 | this->_registers.sp++);

    const std::uint8_t low  = this->read(0x0100 | this->_registers.sp++);
    const std::uint8_t high = this->read(0x0100 | this->_registers.sp);

    this->_registers.pc = (high << 8) | low;

    (void)this->read(this->_registers.pc++);

    RETURN_CYCLE_COUNT(6);
  }

  case OpCode::SBC::Immediate: {
    const std::uint8_t value = this->read(this->_registers.pc++);
    const std::uint8_t a     = this->_registers.a;

    const std::int16_t result = static_cast<std::int16_t>(a) - static_cast<std::int16_t>(value) -
                                !this->_registers.is_carry_set();

    this->_registers.a = static_cast<std::uint8_t>(result);

    this->_registers.set_carry(result >= 0x00);
    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_overflow((result ^ a) & (result ^ ~value) & 0x80);
    this->_registers.set_negative(this->_registers.a & 0x80);

    RETURN_CYCLE_COUNT(2);
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
    break;
  }

  case OpCode::SBC::IndirectIndexed: {
    break;
  }

  case OpCode::SEC::Implied: {
    this->_registers.set_carry(true);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::SED::Implied: {
    this->_registers.set_decimal_mode(true);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::SEI::Implied: {
    this->_registers.set_interrupt_disable(true);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::STA::ZeroPage: {
    const std::uint8_t addr = this->read(this->_registers.pc++);

    this->write(addr, this->_registers.a);

    RETURN_CYCLE_COUNT(3);
  }

  case OpCode::STA::ZeroPageX: {
    const std::uint8_t addr = this->read(this->_registers.pc++);

    (void)this->read(addr);

    const std::uint8_t final_addr = static_cast<std::uint8_t>(addr + this->_registers.x);

    this->write(final_addr, this->_registers.a);

    RETURN_CYCLE_COUNT(4);
  }

  case OpCode::STA::Absolute: {
    const std::uint8_t low   = this->read(this->_registers.pc++);
    const std::uint8_t high  = this->read(this->_registers.pc++);
    const std::uint16_t addr = (high << 8) | low;

    this->write(addr, this->_registers.a);

    RETURN_CYCLE_COUNT(4);
  }

  case OpCode::STA::AbsoluteX: {
    break;
  }

  case OpCode::STA::AbsoluteY: {
    break;
  }

  case OpCode::STA::IndexedIndirect: {
    break;
  }

  case OpCode::STA::IndirectIndexed: {
    break;
  }

  case OpCode::STX::ZeroPage: {
    const auto addr = this->read(this->_registers.pc++);
    this->write(addr, this->_registers.x);

    RETURN_CYCLE_COUNT(3);
  }

  case OpCode::STX::ZeroPageY: {
    break;
  }

  case OpCode::STX::Absolute: {
    const std::uint8_t low   = this->read(this->_registers.pc++);
    const std::uint8_t high  = this->read(this->_registers.pc++);
    const std::uint16_t addr = (high << 8) | low;

    this->write(addr, this->_registers.x);

    RETURN_CYCLE_COUNT(4);
  }

  case OpCode::STY::ZeroPage: {
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

    this->_registers.x = this->_registers.a;

    this->_registers.set_zero(this->_registers.x == 0);
    this->_registers.set_negative(this->_registers.x & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::TAY::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.y = this->_registers.a;

    this->_registers.set_zero(this->_registers.y == 0);
    this->_registers.set_negative(this->_registers.y & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::TSX::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.x = this->_registers.sp;

    this->_registers.set_zero(this->_registers.x == 0);
    this->_registers.set_negative(this->_registers.x & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::TXA::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.a = this->_registers.x;

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::TXS::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.sp = this->_registers.x;

    RETURN_CYCLE_COUNT(2);
  }

  case OpCode::TYA::Implied: {
    (void)this->read(this->_registers.pc);

    this->_registers.a = this->_registers.y;

    this->_registers.set_zero(this->_registers.a == 0);
    this->_registers.set_negative(this->_registers.a & 0x80);

    RETURN_CYCLE_COUNT(2);
  }
  }

  return -1;
}
