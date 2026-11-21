#include <filesystem>
#include <fstream>
#include <regex>
#include <system_error>

#include <gtest/gtest.h>

#include "cpu.hpp"

TEST(CPU, NESTest) {
  std::ifstream rom_file("../tests/data/nestest/nestest.nes", std::ios::binary | std::ios::ate);
  std::ifstream log_file("../tests/data/nestest/nestest.log");

  if (!rom_file) {
    FAIL() << "Failed to open nestest.nes: " << std::error_code(errno, std::generic_category()).message();
  }

  if (!log_file) {
    FAIL() << "Failed to open nestest.log: " << std::error_code(errno, std::generic_category()).message();
  }

  const auto size = rom_file.tellg();

  if (size < 0) {
    FAIL() << "Failed to determine file size";
  }

  std::vector<std::uint8_t> data(static_cast<std::size_t>(size));

  rom_file.seekg(0, std::ios::beg);

  if (!rom_file.read(reinterpret_cast<char*>(data.data()), size)) {
    FAIL() << "Failed to read ROM";
  }

  if (data.size() < 16 || data[0] != 'N' || data[1] != 'E' || data[2] != 'S' || data[3] != 0x1A) {
    FAIL() << "Invalid NES ROM header";
  }

  const std::size_t prg_size = data[4] * 16'384;
  const std::size_t chr_size = data[5] * 8'192;
  const bool has_trainer     = (data[6] & 0x04) != 0;

  const std::size_t prg_offset = 16 + (has_trainer ? 512 : 0);

  if (prg_size != 16'384 && prg_size != 32'768) {
    FAIL() << ("Expected 16 KB or 32 KB PRG-ROM");
  }

  if (prg_offset > data.size() || prg_size > data.size() - prg_offset) {
    FAIL() << ("Invalid PRG-ROM size");
  }

  const auto mapper = (data[6] >> 4) | (data[7] & 0xF0);

  if (mapper != 0) {
    FAIL() << "Only Mapper 0 is supported";
  }

  std::array<std::uint8_t, 65'536> memory{};

  std::copy_n(data.begin() + prg_offset, prg_size, memory.begin() + 0x8000);

  if (prg_size == 16'384) {
    std::copy_n(memory.begin() + 0x8000, 16'384, memory.begin() + 0xC000);
  }

  const std::regex pattern(
      R"(^([0-9A-F]{4})\s+.*A:([0-9A-F]{2})\s+X:([0-9A-F]{2})\s+Y:([0-9A-F]{2})\s+P:([0-9A-F]{2})\s+SP:([0-9A-F]{2}).*CYC:\s*(\d+))");

  CPU cpu{memory};

  const CPU::Registers registers{
      .pc = 0xC000,
      .a  = 0x00,
      .x  = 0x00,
      .y  = 0x00,
      .p  = 0x24,
      .sp = 0xFD,
  };

  cpu.set_test_state(registers, memory, 7);

  std::string line;
  std::size_t instruction = 0;

  while (std::getline(log_file, line)) {
    std::smatch match;

    if (!std::regex_search(line, match, pattern)) {
      throw std::runtime_error("Failed to parse nestest.log");
    }

    auto hex = [&](int index) -> std::uint32_t {
      return static_cast<std::uint32_t>(std::stoul(match[index].str(), nullptr, 16));
    };

    const CPU::Registers actual   = cpu.get_registers();
    const CPU::Registers expected = {
        .pc = static_cast<std::uint16_t>(hex(1)),
        .a  = static_cast<std::uint8_t>(hex(2)),
        .x  = static_cast<std::uint8_t>(hex(3)),
        .y  = static_cast<std::uint8_t>(hex(4)),
        .p  = static_cast<std::uint8_t>(hex(5)),
        .sp = static_cast<std::uint8_t>(hex(6)),
    };

    const std::uint64_t actual_cycles   = cpu.get_cycle_count();
    const std::uint64_t expected_cycles = std::stoull(match[7].str());

    SCOPED_TRACE("Line #" + std::to_string(instruction + 1) + ": " + line);

    ASSERT_EQ(actual.pc, expected.pc) << "PC mismatch";
    ASSERT_EQ(actual.a, expected.a) << "Accumulator mismatch";
    ASSERT_EQ(actual.x, expected.x) << "X register mismatch";
    ASSERT_EQ(actual.y, expected.y) << "Y register mismatch";

    ASSERT_EQ(actual.is_carry_set(), expected.is_carry_set()) << "Carry flag mismatch";
    ASSERT_EQ(actual.is_zero_set(), expected.is_zero_set()) << "Zero flag mismatch";
    ASSERT_EQ(actual.is_interrupt_disable_set(), expected.is_interrupt_disable_set())
        << "Interrupt Disable flag mismatch";
    ASSERT_EQ(actual.is_decimal_mode_set(), expected.is_decimal_mode_set()) << "Decimal Mode flag mismatch";
    ASSERT_EQ(actual.is_break_command_set(), expected.is_break_command_set()) << "Break Command flag mismatch";
    ASSERT_EQ(actual.is_unused_set(), expected.is_unused_set()) << "Unused flag mismatch";
    ASSERT_EQ(actual.is_overflow_set(), expected.is_overflow_set()) << "Overflow flag mismatch";
    ASSERT_EQ(actual.is_negative_set(), expected.is_negative_set()) << "Negative flag mismatch";

    ASSERT_EQ(actual.p, expected.p) << "Processor status mismatch";

    ASSERT_EQ(actual.sp, expected.sp) << "Stack pointer mismatch";
    ASSERT_EQ(actual_cycles, expected_cycles) << "Cycle count mismatch";

    if (cpu.step() < 2) {
      FAIL() << "Unhandled opcode encountered at line #" << instruction + 1;
    }

    ++instruction;
  }
}
