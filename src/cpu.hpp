#pragma once

#include <cstdint>

#include "bus.hpp"

class CPU {
public:
  explicit CPU(Bus& bus);
  ~CPU();

  struct State {
    std::uint16_t pc{};
    std::uint8_t a{};
    std::uint8_t x{};
    std::uint8_t y{};
    std::uint8_t p{};
    std::uint8_t sp{};
    std::uint64_t cycles{};
  };

  struct Registers {
    std::uint16_t pc{};
    std::uint8_t a{};
    std::uint8_t x{};
    std::uint8_t y{};
    std::uint8_t p{};
    std::uint8_t sp{};

    [[nodiscard]] bool is_carry_set() const { return p & 0x01; }
    [[nodiscard]] bool is_carry_clear() const { return !is_carry_set(); }
    void set_carry(bool value) { this->set_flag(0x01, value); }

    [[nodiscard]] bool is_zero_set() const { return p & 0x02; }
    [[nodiscard]] bool is_zero_clear() const { return !is_zero_set(); }
    void set_zero(bool value) { this->set_flag(0x02, value); }

    [[nodiscard]] bool is_interrupt_disable_set() const { return p & 0x04; }
    [[nodiscard]] bool is_interrupt_disable_clear() const { return !is_interrupt_disable_set(); }
    void set_interrupt_disable(bool value) { this->set_flag(0x04, value); }

    [[nodiscard]] bool is_decimal_mode_set() const { return p & 0x08; }
    [[nodiscard]] bool is_decimal_mode_clear() const { return !is_decimal_mode_set(); }
    void set_decimal_mode(bool value) { this->set_flag(0x08, value); }

    [[nodiscard]] bool is_break_command_set() const { return p & 0x10; }
    [[nodiscard]] bool is_break_command_clear() const { return !is_break_command_set(); }
    void set_break_command(bool value) { this->set_flag(0x10, value); }

    [[nodiscard]] bool is_unused_set() const { return p & 0x20; }
    [[nodiscard]] bool is_unused_clear() const { return !is_unused_set(); }
    void set_unused(bool value) { this->set_flag(0x20, value); }

    [[nodiscard]] bool is_overflow_set() const { return p & 0x40; }
    [[nodiscard]] bool is_overflow_clear() const { return !is_overflow_set(); }
    void set_overflow(bool value) { this->set_flag(0x40, value); }

    [[nodiscard]] bool is_negative_set() const { return p & 0x80; }
    [[nodiscard]] bool is_negative_clear() const { return !is_negative_set(); }
    void set_negative(bool value) { this->set_flag(0x80, value); }

    bool operator==(const Registers&) const = default;

  private:
    inline void set_flag(const std::uint8_t mask, const bool value) {
      if (value) {
        this->p |= mask;
      } else {
        this->p &= static_cast<std::uint8_t>(~mask);
      }
    }
  };

  std::uint8_t step();
  [[nodiscard]] State get_state() const {
    return {
        .pc     = this->_registers.pc,
        .a      = this->_registers.a,
        .x      = this->_registers.x,
        .y      = this->_registers.y,
        .p      = this->_registers.p,
        .sp     = this->_registers.sp,
        .cycles = this->_total_cycle_count,
    };
  }

  void set_state(const State& state) {
    this->_registers.a         = state.a;
    this->_registers.x         = state.x;
    this->_registers.y         = state.y;
    this->_registers.pc        = state.pc;
    this->_registers.sp        = state.sp;
    this->_registers.p         = state.p;
    this->_total_cycle_count   = state.cycles;
    this->_current_cycle_count = 0;
  }

private:
  static constexpr std::uint8_t UNSTABLE_MAGIC = 0xEE;

  Bus& _bus;
  Registers _registers{};
  std::uint64_t _total_cycle_count{};
  std::uint8_t _current_cycle_count{};

  void tick();

  [[nodiscard]] std::uint8_t read(std::uint16_t addr);
  void write(std::uint16_t addr, std::uint8_t value);

  [[nodiscard]] std::uint8_t read_stack();
  [[nodiscard]] std::uint8_t pop_stack();
  void push_stack(std::uint8_t value);

  [[nodiscard]] std::uint8_t read_zero_page();
  [[nodiscard]] std::uint16_t resolve_zero_page();

  [[nodiscard]] std::uint8_t read_zero_page_indexed(std::uint8_t index);
  [[nodiscard]] std::uint16_t resolve_zero_page_indexed(std::uint8_t index);

  [[nodiscard]] std::uint8_t read_absolute();
  [[nodiscard]] std::uint16_t resolve_absolute();

  [[nodiscard]] std::uint8_t read_absolute_indexed(std::uint8_t index);
  [[nodiscard]] std::uint16_t resolve_absolute_indexed(std::uint8_t index);

  [[nodiscard]] std::uint8_t read_indexed_indirect();
  [[nodiscard]] std::uint16_t resolve_indexed_indirect();

  [[nodiscard]] std::uint8_t read_indirect_indexed();
  [[nodiscard]] std::uint16_t resolve_indirect_indexed();

  void bitwise_and(std::uint8_t value);
  void bitwise_or(std::uint8_t value);
  void bitwise_eor(std::uint8_t value);
  std::uint8_t shift_left(std::uint16_t addr);
  std::uint8_t shift_right(std::uint16_t addr);
  std::uint8_t rotate_left(std::uint16_t addr);
  std::uint8_t rotate_right(std::uint16_t addr);
  void branch_if(bool condition);
  void bit_test(std::uint8_t value);
  void compare(std::uint8_t reg, std::uint8_t value);
  void add_with_carry(std::uint8_t value);
  void subtract_with_carry(std::uint8_t value);
  std::uint8_t increment(std::uint16_t addr);
  std::uint8_t decrement(std::uint16_t addr);
  void assign_register(std::uint8_t& reg, std::uint8_t value);

  void write_masked_indexed(std::uint16_t base, std::uint8_t index, std::uint8_t data);
};
