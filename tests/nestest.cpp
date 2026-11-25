#include <filesystem>
#include <fstream>
#include <print>
#include <regex>
#include <system_error>

#include <gtest/gtest.h>

#include "cpu.hpp"
#include "opcode.hpp"
#include "test_bus.hpp"

const char* opcode_to_string(std::uint8_t code);

TEST(CPU_NESTest, NESTest) {
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

  const std::regex pattern(
      R"(^([0-9A-F]{4})\s+.([0-9A-F]{2})\s+.*A:([0-9A-F]{2})\s+X:([0-9A-F]{2})\s+Y:([0-9A-F]{2})\s+P:([0-9A-F]{2})\s+SP:([0-9A-F]{2}).*CYC:\s*(\d+))");

  TestBus bus{};

  for (std::size_t i = 0; i < 0x8000; ++i) {
    bus.write(static_cast<std::uint16_t>(0x8000 + i), data[prg_offset + (i % prg_size)]);
  }

  CPU cpu{bus};

  cpu.set_state(CPU::State{
      .pc     = 0xC000,
      .a      = 0,
      .x      = 0,
      .y      = 0,
      .p      = 0x24,
      .sp     = 0xFD,
      .cycles = 7,
  });

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

    const CPU::State actual   = cpu.get_state();
    const CPU::State expected = {
        .pc     = static_cast<std::uint16_t>(hex(1)),
        .a      = static_cast<std::uint8_t>(hex(3)),
        .x      = static_cast<std::uint8_t>(hex(4)),
        .y      = static_cast<std::uint8_t>(hex(5)),
        .p      = static_cast<std::uint8_t>(hex(6)),
        .sp     = static_cast<std::uint8_t>(hex(7)),
        .cycles = std::stoull(match[8].str(), nullptr, 10),
    };

    SCOPED_TRACE("Line #" + std::to_string(instruction + 1) + ": " + line);

    ASSERT_EQ(actual.pc, expected.pc) << "PC mismatch";
    ASSERT_EQ(actual.a, expected.a) << "Accumulator mismatch";
    ASSERT_EQ(actual.x, expected.x) << "X register mismatch";
    ASSERT_EQ(actual.y, expected.y) << "Y register mismatch";

    ASSERT_EQ(actual.p & 0x01, expected.p & 0x01) << "Carry flag mismatch";
    ASSERT_EQ(actual.p & 0x02, expected.p & 0x02) << "Zero flag mismatch";
    ASSERT_EQ(actual.p & 0x04, expected.p & 0x04) << "Interrupt Disable flag mismatch";
    ASSERT_EQ(actual.p & 0x08, expected.p & 0x08) << "Decimal Mode flag mismatch";
    ASSERT_EQ(actual.p & 0x10, expected.p & 0x10) << "Break Command flag mismatch";
    ASSERT_EQ(actual.p & 0x20, expected.p & 0x20) << "Unused flag mismatch";
    ASSERT_EQ(actual.p & 0x40, expected.p & 0x40) << "Overflow flag mismatch";
    ASSERT_EQ(actual.p & 0x80, expected.p & 0x80) << "Negative flag mismatch";

    ASSERT_EQ(actual.p, expected.p) << "Processor status mismatch";

    ASSERT_EQ(actual.sp, expected.sp) << "Stack pointer mismatch";
    ASSERT_EQ(actual.cycles, expected.cycles) << "Cycle count mismatch";

    if (cpu.step() < 2) {
      FAIL() << "Unhandled OpCode on line " << instruction + 1 << ": " << opcode_to_string(hex(2));
    }

    ++instruction;
  }
}

const char* opcode_to_string(const std::uint8_t code) {
  switch (code) {
  case OpCode::ADC::Immediate:
    return "ADC::Immediate";
  case OpCode::ADC::ZeroPage:
    return "ADC::ZeroPage";
  case OpCode::ADC::ZeroPageX:
    return "ADC::ZeroPageX";
  case OpCode::ADC::Absolute:
    return "ADC::Absolute";
  case OpCode::ADC::AbsoluteX:
    return "ADC::AbsoluteX";
  case OpCode::ADC::AbsoluteY:
    return "ADC::AbsoluteY";
  case OpCode::ADC::IndexedIndirect:
    return "ADC::IndexedIndirect";
  case OpCode::ADC::IndirectIndexed:
    return "ADC::IndirectIndexed";
  case OpCode::AND::Immediate:
    return "AND::Immediate";
  case OpCode::AND::ZeroPage:
    return "AND::ZeroPage";
  case OpCode::AND::ZeroPageX:
    return "AND::ZeroPageX";
  case OpCode::AND::Absolute:
    return "AND::Absolute";
  case OpCode::AND::AbsoluteX:
    return "AND::AbsoluteX";
  case OpCode::AND::AbsoluteY:
    return "AND::AbsoluteY";
  case OpCode::AND::IndexedIndirect:
    return "AND::IndexedIndirect";
  case OpCode::AND::IndirectIndexed:
    return "AND::IndirectIndexed";
  case OpCode::ASL::Accumulator:
    return "ASL::Accumulator";
  case OpCode::ASL::ZeroPage:
    return "ASL::ZeroPage";
  case OpCode::ASL::ZeroPageX:
    return "ASL::ZeroPageX";
  case OpCode::ASL::Absolute:
    return "ASL::Absolute";
  case OpCode::ASL::AbsoluteX:
    return "ASL::AbsoluteX";
  case OpCode::BCC::Relative:
    return "BCC::Relative";
  case OpCode::BCS::Relative:
    return "BCS::Relative";
  case OpCode::BEQ::Relative:
    return "BEQ::Relative";
  case OpCode::BIT::ZeroPage:
    return "BIT::ZeroPage";
  case OpCode::BIT::Absolute:
    return "BIT::Absolute";
  case OpCode::BMI::Relative:
    return "BMI::Relative";
  case OpCode::BNE::Relative:
    return "BNE::Relative";
  case OpCode::BPL::Relative:
    return "BPL::Relative";
  case OpCode::BRK::Implied:
    return "BRK::Implied";
  case OpCode::BVC::Relative:
    return "BVC::Relative";
  case OpCode::BVS::Relative:
    return "BVS::Relative";
  case OpCode::CLC::Implied:
    return "CLC::Implied";
  case OpCode::CLD::Implied:
    return "CLD::Implied";
  case OpCode::CLI::Implied:
    return "CLI::Implied";
  case OpCode::CLV::Implied:
    return "CLV::Implied";
  case OpCode::CMP::Immediate:
    return "CMP::Immediate";
  case OpCode::CMP::ZeroPage:
    return "CMP::ZeroPage";
  case OpCode::CMP::ZeroPageX:
    return "CMP::ZeroPageX";
  case OpCode::CMP::Absolute:
    return "CMP::Absolute";
  case OpCode::CMP::AbsoluteX:
    return "CMP::AbsoluteX";
  case OpCode::CMP::AbsoluteY:
    return "CMP::AbsoluteY";
  case OpCode::CMP::IndexedIndirect:
    return "CMP::IndexedIndirect";
  case OpCode::CMP::IndirectIndexed:
    return "CMP::IndirectIndexed";
  case OpCode::CPX::Immediate:
    return "CPX::Immediate";
  case OpCode::CPX::ZeroPage:
    return "CPX::ZeroPage";
  case OpCode::CPX::Absolute:
    return "CPX::Absolute";
  case OpCode::CPY::Immediate:
    return "CPY::Immediate";
  case OpCode::CPY::ZeroPage:
    return "CPY::ZeroPage";
  case OpCode::CPY::Absolute:
    return "CPY::Absolute";
  case OpCode::DEC::ZeroPage:
    return "DEC::ZeroPage";
  case OpCode::DEC::ZeroPageX:
    return "DEC::ZeroPageX";
  case OpCode::DEC::Absolute:
    return "DEC::Absolute";
  case OpCode::DEC::AbsoluteX:
    return "DEC::AbsoluteX";
  case OpCode::DEX::Implied:
    return "DEX::Implied";
  case OpCode::DEY::Implied:
    return "DEY::Implied";
  case OpCode::EOR::Immediate:
    return "EOR::Immediate";
  case OpCode::EOR::ZeroPage:
    return "EOR::ZeroPage";
  case OpCode::EOR::ZeroPageX:
    return "EOR::ZeroPageX";
  case OpCode::EOR::Absolute:
    return "EOR::Absolute";
  case OpCode::EOR::AbsoluteX:
    return "EOR::AbsoluteX";
  case OpCode::EOR::AbsoluteY:
    return "EOR::AbsoluteY";
  case OpCode::EOR::IndexedIndirect:
    return "EOR::IndexedIndirect";
  case OpCode::EOR::IndirectIndexed:
    return "EOR::IndirectIndexed";
  case OpCode::INC::ZeroPage:
    return "INC::ZeroPage";
  case OpCode::INC::ZeroPageX:
    return "INC::ZeroPageX";
  case OpCode::INC::Absolute:
    return "INC::Absolute";
  case OpCode::INC::AbsoluteX:
    return "INC::AbsoluteX";
  case OpCode::INX::Implied:
    return "INX::Implied";
  case OpCode::INY::Implied:
    return "INY::Implied";
  case OpCode::JMP::Absolute:
    return "JMP::Absolute";
  case OpCode::JMP::Indirect:
    return "JMP::Indirect";
  case OpCode::JSR::Absolute:
    return "JSR::Absolute";
  case OpCode::LDA::Immediate:
    return "LDA::Immediate";
  case OpCode::LDA::ZeroPage:
    return "LDA::ZeroPage";
  case OpCode::LDA::ZeroPageX:
    return "LDA::ZeroPageX";
  case OpCode::LDA::Absolute:
    return "LDA::Absolute";
  case OpCode::LDA::AbsoluteX:
    return "LDA::AbsoluteX";
  case OpCode::LDA::AbsoluteY:
    return "LDA::AbsoluteY";
  case OpCode::LDA::IndexedIndirect:
    return "LDA::IndexedIndirect";
  case OpCode::LDA::IndirectIndexed:
    return "LDA::IndirectIndexed";
  case OpCode::LDX::Immediate:
    return "LDX::Immediate";
  case OpCode::LDX::ZeroPage:
    return "LDX::ZeroPage";
  case OpCode::LDX::ZeroPageY:
    return "LDX::ZeroPageY";
  case OpCode::LDX::Absolute:
    return "LDX::Absolute";
  case OpCode::LDX::AbsoluteY:
    return "LDX::AbsoluteY";
  case OpCode::LDY::Immediate:
    return "LDY::Immediate";
  case OpCode::LDY::ZeroPage:
    return "LDY::ZeroPage";
  case OpCode::LDY::ZeroPageX:
    return "LDY::ZeroPageX";
  case OpCode::LDY::Absolute:
    return "LDY::Absolute";
  case OpCode::LDY::AbsoluteX:
    return "LDY::AbsoluteX";
  case OpCode::LSR::Accumulator:
    return "LSR::Accumulator";
  case OpCode::LSR::ZeroPage:
    return "LSR::ZeroPage";
  case OpCode::LSR::ZeroPageX:
    return "LSR::ZeroPageX";
  case OpCode::LSR::Absolute:
    return "LSR::Absolute";
  case OpCode::LSR::AbsoluteX:
    return "LSR::AbsoluteX";
  case OpCode::NOP::Implied:
    return "NOP::Implied";
  case OpCode::ORA::Immediate:
    return "ORA::Immediate";
  case OpCode::ORA::ZeroPage:
    return "ORA::ZeroPage";
  case OpCode::ORA::ZeroPageX:
    return "ORA::ZeroPageX";
  case OpCode::ORA::Absolute:
    return "ORA::Absolute";
  case OpCode::ORA::AbsoluteX:
    return "ORA::AbsoluteX";
  case OpCode::ORA::AbsoluteY:
    return "ORA::AbsoluteY";
  case OpCode::ORA::IndexedIndirect:
    return "ORA::IndexedIndirect";
  case OpCode::ORA::IndirectIndexed:
    return "ORA::IndirectIndexed";
  case OpCode::PHA::Implied:
    return "PHA::Implied";
  case OpCode::PHP::Implied:
    return "PHP::Implied";
  case OpCode::PLA::Implied:
    return "PLA::Implied";
  case OpCode::PLP::Implied:
    return "PLP::Implied";
  case OpCode::ROL::Accumulator:
    return "ROL::Accumulator";
  case OpCode::ROL::ZeroPage:
    return "ROL::ZeroPage";
  case OpCode::ROL::ZeroPageX:
    return "ROL::ZeroPageX";
  case OpCode::ROL::Absolute:
    return "ROL::Absolute";
  case OpCode::ROL::AbsoluteX:
    return "ROL::AbsoluteX";
  case OpCode::ROR::Accumulator:
    return "ROR::Accumulator";
  case OpCode::ROR::ZeroPage:
    return "ROR::ZeroPage";
  case OpCode::ROR::ZeroPageX:
    return "ROR::ZeroPageX";
  case OpCode::ROR::Absolute:
    return "ROR::Absolute";
  case OpCode::ROR::AbsoluteX:
    return "ROR::AbsoluteX";
  case OpCode::RTI::Implied:
    return "RTI::Implied";
  case OpCode::RTS::Implied:
    return "RTS::Implied";
  case OpCode::SBC::Immediate:
    return "SBC::Immediate";
  case OpCode::SBC::ZeroPage:
    return "SBC::ZeroPage";
  case OpCode::SBC::ZeroPageX:
    return "SBC::ZeroPageX";
  case OpCode::SBC::Absolute:
    return "SBC::Absolute";
  case OpCode::SBC::AbsoluteX:
    return "SBC::AbsoluteX";
  case OpCode::SBC::AbsoluteY:
    return "SBC::AbsoluteY";
  case OpCode::SBC::IndexedIndirect:
    return "SBC::IndexedIndirect";
  case OpCode::SBC::IndirectIndexed:
    return "SBC::IndirectIndexed";
  case OpCode::SEC::Implied:
    return "SEC::Implied";
  case OpCode::SED::Implied:
    return "SED::Implied";
  case OpCode::SEI::Implied:
    return "SEI::Implied";
  case OpCode::STA::ZeroPage:
    return "STA::ZeroPage";
  case OpCode::STA::ZeroPageX:
    return "STA::ZeroPageX";
  case OpCode::STA::Absolute:
    return "STA::Absolute";
  case OpCode::STA::AbsoluteX:
    return "STA::AbsoluteX";
  case OpCode::STA::AbsoluteY:
    return "STA::AbsoluteY";
  case OpCode::STA::IndexedIndirect:
    return "STA::IndexedIndirect";
  case OpCode::STA::IndirectIndexed:
    return "STA::IndirectIndexed";
  case OpCode::STX::ZeroPage:
    return "STX::ZeroPage";
  case OpCode::STX::ZeroPageY:
    return "STX::ZeroPageY";
  case OpCode::STX::Absolute:
    return "STX::Absolute";
  case OpCode::STY::ZeroPage:
    return "STY::ZeroPage";
  case OpCode::STY::ZeroPageX:
    return "STY::ZeroPageX";
  case OpCode::STY::Absolute:
    return "STY::Absolute";
  case OpCode::TAX::Implied:
    return "TAX::Implied";
  case OpCode::TAY::Implied:
    return "TAY::Implied";
  case OpCode::TSX::Implied:
    return "TSX::Implied";
  case OpCode::TXA::Implied:
    return "TXA::Implied";
  case OpCode::TXS::Implied:
    return "TXS::Implied";
  case OpCode::TYA::Implied:
    return "TYA::Implied";
  default:
    return "Unknown OpCode";
  }
}
