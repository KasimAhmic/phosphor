#pragma once

#include <array>
#include <cstdint>

class CPU {
public:
  CPU(std::array<std::uint8_t, 65536> memory);
  ~CPU();

  struct Registers {

    std::uint16_t pc;
    std::uint8_t a;
    std::uint8_t x;
    std::uint8_t y;
    std::uint8_t p;
    std::uint8_t sp;

    bool is_carry_set() const { return p & 0x01; }
    bool is_carry_clear() const { return !is_carry_set(); }
    void set_carry(bool value) { value ? p |= 0x01 : p &= ~0x01; }

    bool is_zero_set() const { return p & 0x02; }
    bool is_zero_clear() const { return !is_zero_set(); }
    void set_zero(bool value) { value ? p |= 0x02 : p &= ~0x02; }

    bool is_interrupt_disable_set() const { return p & 0x04; }
    bool is_interrupt_disable_clear() const { return !is_interrupt_disable_set(); }
    void set_interrupt_disable(bool value) { value ? p |= 0x04 : p &= ~0x04; }

    bool is_decimal_mode_set() const { return p & 0x08; }
    bool is_decimal_mode_clear() const { return !is_decimal_mode_set(); }
    void set_decimal_mode(bool value) { value ? p |= 0x08 : p &= ~0x08; }

    bool is_break_command_set() const { return p & 0x10; }
    bool is_break_command_clear() const { return !is_break_command_set(); }
    void set_break_command(bool value) { value ? p |= 0x10 : p &= ~0x10; }

    bool is_unused_set() const { return p & 0x20; }
    bool is_unused_clear() const { return !is_unused_set(); }
    void set_unused(bool value) { value ? p |= 0x20 : p &= ~0x20; }

    bool is_overflow_set() const { return p & 0x40; }
    bool is_overflow_clear() const { return !is_overflow_set(); }
    void set_overflow(bool value) { value ? p |= 0x40 : p &= ~0x40; }

    bool is_negative_set() const { return p & 0x80; }
    bool is_negative_clear() const { return !is_negative_set(); }
    void set_negative(bool value) { value ? p |= 0x80 : p &= ~0x80; }

    bool operator==(const Registers&) const = default;
  };

  void reset();
  std::int8_t step();

  std::uint16_t get_program_counter() const { return this->_registers.pc; }
  void set_program_counter(std::uint16_t pc) { this->_registers.pc = pc; }

  std::uint64_t get_cycle_count() const { return this->_total_cycle_count; }
  std::array<std::uint8_t, 65536> get_memory() const { return this->_memory; }
  Registers get_registers() const { return this->_registers; }

private:
  std::uint8_t read(std::uint16_t addr);
  void write(std::uint16_t addr, std::uint8_t value);
  void tick();

  Registers _registers;
  std::uint64_t _total_cycle_count;
  std::uint8_t _current_cycle_count;
  std::array<std::uint8_t, 65536> _memory;

  void add_with_carry(std::uint8_t value);
  void bitwise_and(std::uint8_t value);
  void branch_if(bool condition);
  void compare(std::uint8_t value);
};
