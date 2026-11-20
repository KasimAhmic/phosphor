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

    bool is_carry_set() const { return p >> 0 & 1; }
    bool is_zero_set() const { return p >> 1 & 1; }
    bool is_interrupt_disable_set() const { return p >> 2 & 1; }
    bool is_decimal_mode_set() const { return p >> 3 & 1; }
    bool is_break_command_set() const { return p >> 4 & 1; }
    bool is_unused_set() const { return p >> 5 & 1; }
    bool is_overflow_set() const { return p >> 6 & 1; }
    bool is_negative_set() const { return p >> 7 & 1; }

    bool operator==(const Registers&) const = default;
  };

  void reset();
  std::int8_t step();

  std::uint16_t get_program_counter() const { return this->_registers.pc; }
  void set_program_counter(std::uint16_t pc) { this->_registers.pc = pc; }

  std::uint64_t get_cycle_count() const { return this->_cycle_count; }
  std::array<std::uint8_t, 65536> get_memory() const { return this->_memory; }
  Registers get_registers() const { return this->_registers; }

private:
  std::uint8_t read(std::uint16_t addr);
  void write(std::uint16_t addr, std::uint8_t value);
  void tick();

  Registers _registers;
  std::uint64_t _cycle_count;
  std::array<std::uint8_t, 65536> _memory;
};
