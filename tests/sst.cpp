#include <filesystem>
#include <fstream>
#include <regex>
#include <system_error>

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "cpu.hpp"

using nlohmann::json;

constexpr std::size_t MEMORY_SIZE = 65536;

// B and unused are not conventional persistent hardware flags
constexpr std::uint8_t STATUS_MASK = 0xCF;

void run_single_step_tests(const std::string& filename) {
  const std::filesystem::path path{"../tests/data/sst/" + filename + ".json"};

  std::ifstream file(path);

  ASSERT_TRUE(file.is_open()) << "Could not open " << path.string();

  json tests;
  ASSERT_NO_THROW(file >> tests);

  for (const auto& test : tests) {
    SCOPED_TRACE(test.at("name").get<std::string>());

    const auto& initial  = test.at("initial");
    const auto& expected = test.at("final");
    const auto& cycles   = test.at("cycles");

    std::array<std::uint8_t, MEMORY_SIZE> memory{};

    for (const auto& entry : initial.at("ram")) {
      const auto addr  = entry.at(0).get<std::uint16_t>();
      const auto value = entry.at(1).get<std::uint8_t>();

      memory[addr] = value;
    }

    CPU::Registers registers{};
    registers.pc = initial.at("pc").get<std::uint16_t>();
    registers.sp = initial.at("s").get<std::uint8_t>();
    registers.a  = initial.at("a").get<std::uint8_t>();
    registers.x  = initial.at("x").get<std::uint8_t>();
    registers.y  = initial.at("y").get<std::uint8_t>();
    registers.p  = initial.at("p").get<std::uint8_t>();

    CPU cpu{memory};
    cpu.set_test_state(registers, memory, 0);

    const int executed_cycles = cpu.step();
    const auto actual         = cpu.get_registers();

    EXPECT_EQ(actual.pc, expected.at("pc").get<std::uint16_t>()) << "PC mismatch";
    EXPECT_EQ(actual.sp, expected.at("s").get<std::uint8_t>()) << "SP mismatch";
    EXPECT_EQ(actual.a, expected.at("a").get<std::uint8_t>()) << "A mismatch";
    EXPECT_EQ(actual.x, expected.at("x").get<std::uint8_t>()) << "X mismatch";
    EXPECT_EQ(actual.y, expected.at("y").get<std::uint8_t>()) << "Y mismatch";

    const auto expected_p = expected.at("p").get<std::uint8_t>();

    EXPECT_EQ(actual.p & STATUS_MASK, expected_p & STATUS_MASK) << "Status flags mismatch";

    ASSERT_EQ(executed_cycles, static_cast<int>(cycles.size())) << "Cycle count mismatch";

    const auto& actual_memory = cpu.get_memory();

    for (const auto& entry : expected.at("ram")) {
      const auto addr  = entry.at(0).get<std::uint16_t>();
      const auto value = entry.at(1).get<std::uint8_t>();

      EXPECT_EQ(actual_memory[addr], value) << "Memory mismatch at " << addr;
    }
  }
}

// Official OpCodes
TEST(CPU_SST, BRK) { run_single_step_tests("00"); }
TEST(CPU_SST, ORA_IndexedIndirect) { run_single_step_tests("01"); }
TEST(CPU_SST, ORA_ZeroPage) { run_single_step_tests("05"); }
TEST(CPU_SST, ASL_ZeroPage) { run_single_step_tests("06"); }
TEST(CPU_SST, PHP) { run_single_step_tests("08"); }
TEST(CPU_SST, ORA_Immediate) { run_single_step_tests("09"); }
TEST(CPU_SST, ASL_Accumulator) { run_single_step_tests("0a"); }
TEST(CPU_SST, ORA_Absolute) { run_single_step_tests("0d"); }
TEST(CPU_SST, ASL_Absolute) { run_single_step_tests("0e"); }
TEST(CPU_SST, BPL_Relative) { run_single_step_tests("10"); }
TEST(CPU_SST, ORA_IndirectIndexed) { run_single_step_tests("11"); }
TEST(CPU_SST, ORA_ZeroPageX) { run_single_step_tests("15"); }
TEST(CPU_SST, ASL_ZeroPageX) { run_single_step_tests("16"); }
TEST(CPU_SST, CLC) { run_single_step_tests("18"); }
TEST(CPU_SST, ORA_AbsoluteY) { run_single_step_tests("19"); }
TEST(CPU_SST, ORA_AbsoluteX) { run_single_step_tests("1d"); }
TEST(CPU_SST, ASL_AbsoluteX) { run_single_step_tests("1e"); }
TEST(CPU_SST, JSR_Absolute) { run_single_step_tests("20"); }
TEST(CPU_SST, AND_IndexedIndirect) { run_single_step_tests("21"); }
TEST(CPU_SST, BIT_ZeroPage) { run_single_step_tests("24"); }
TEST(CPU_SST, AND_ZeroPage) { run_single_step_tests("25"); }
TEST(CPU_SST, ROL_ZeroPage) { run_single_step_tests("26"); }
TEST(CPU_SST, PLP) { run_single_step_tests("28"); }
TEST(CPU_SST, AND_Immediate) { run_single_step_tests("29"); }
TEST(CPU_SST, ROL_Accumulator) { run_single_step_tests("2a"); }
TEST(CPU_SST, BIT_Absolute) { run_single_step_tests("2c"); }
TEST(CPU_SST, AND_Absolute) { run_single_step_tests("2d"); }
TEST(CPU_SST, ROL_Absolute) { run_single_step_tests("2e"); }
TEST(CPU_SST, BMI_Relative) { run_single_step_tests("30"); }
TEST(CPU_SST, AND_IndirectIndexed) { run_single_step_tests("31"); }
TEST(CPU_SST, AND_ZeroPageX) { run_single_step_tests("35"); }
TEST(CPU_SST, ROL_ZeroPageX) { run_single_step_tests("36"); }
TEST(CPU_SST, SEC) { run_single_step_tests("38"); }
TEST(CPU_SST, AND_AbsoluteY) { run_single_step_tests("39"); }
TEST(CPU_SST, AND_AbsoluteX) { run_single_step_tests("3d"); }
TEST(CPU_SST, ROL_AbsoluteX) { run_single_step_tests("3e"); }
TEST(CPU_SST, RTI) { run_single_step_tests("40"); }
TEST(CPU_SST, EOR_IndexedIndirect) { run_single_step_tests("41"); }
TEST(CPU_SST, EOR_ZeroPage) { run_single_step_tests("45"); }
TEST(CPU_SST, LSR_ZeroPage) { run_single_step_tests("46"); }
TEST(CPU_SST, PHA) { run_single_step_tests("48"); }
TEST(CPU_SST, EOR_Immediate) { run_single_step_tests("49"); }
TEST(CPU_SST, LSR_Accumulator) { run_single_step_tests("4a"); }
TEST(CPU_SST, JMP_Absolute) { run_single_step_tests("4c"); }
TEST(CPU_SST, EOR_Absolute) { run_single_step_tests("4d"); }
TEST(CPU_SST, LSR_Absolute) { run_single_step_tests("4e"); }
TEST(CPU_SST, BVC_Relative) { run_single_step_tests("50"); }
TEST(CPU_SST, EOR_IndirectIndexed) { run_single_step_tests("51"); }
TEST(CPU_SST, EOR_ZeroPageX) { run_single_step_tests("55"); }
TEST(CPU_SST, LSR_ZeroPageX) { run_single_step_tests("56"); }
TEST(CPU_SST, CLI) { run_single_step_tests("58"); }
TEST(CPU_SST, EOR_AbsoluteY) { run_single_step_tests("59"); }
TEST(CPU_SST, EOR_AbsoluteX) { run_single_step_tests("5d"); }
TEST(CPU_SST, LSR_AbsoluteX) { run_single_step_tests("5e"); }
TEST(CPU_SST, RTS) { run_single_step_tests("60"); }
TEST(CPU_SST, ADC_IndexedIndirect) { run_single_step_tests("61"); }
TEST(CPU_SST, ADC_ZeroPage) { run_single_step_tests("65"); }
TEST(CPU_SST, ROR_ZeroPage) { run_single_step_tests("66"); }
TEST(CPU_SST, PLA) { run_single_step_tests("68"); }
TEST(CPU_SST, ADC_Immediate) { run_single_step_tests("69"); }
TEST(CPU_SST, ROR_Accumulator) { run_single_step_tests("6a"); }
TEST(CPU_SST, JMP_Indirect) { run_single_step_tests("6c"); }
TEST(CPU_SST, ADC_Absolute) { run_single_step_tests("6d"); }
TEST(CPU_SST, ROR_Absolute) { run_single_step_tests("6e"); }
TEST(CPU_SST, BVS_Relative) { run_single_step_tests("70"); }
TEST(CPU_SST, ADC_IndirectIndexed) { run_single_step_tests("71"); }
TEST(CPU_SST, ADC_ZeroPageX) { run_single_step_tests("75"); }
TEST(CPU_SST, ROR_ZeroPageX) { run_single_step_tests("76"); }
TEST(CPU_SST, SEI) { run_single_step_tests("78"); }
TEST(CPU_SST, ADC_AbsoluteY) { run_single_step_tests("79"); }
TEST(CPU_SST, ADC_AbsoluteX) { run_single_step_tests("7d"); }
TEST(CPU_SST, ROR_AbsoluteX) { run_single_step_tests("7e"); }
TEST(CPU_SST, STA_IndexedIndirect) { run_single_step_tests("81"); }
TEST(CPU_SST, STY_ZeroPage) { run_single_step_tests("84"); }
TEST(CPU_SST, STA_ZeroPage) { run_single_step_tests("85"); }
TEST(CPU_SST, STX_ZeroPage) { run_single_step_tests("86"); }
TEST(CPU_SST, DEY) { run_single_step_tests("88"); }
TEST(CPU_SST, TXA) { run_single_step_tests("8a"); }
TEST(CPU_SST, STY_Absolute) { run_single_step_tests("8c"); }
TEST(CPU_SST, STA_Absolute) { run_single_step_tests("8d"); }
TEST(CPU_SST, STX_Absolute) { run_single_step_tests("8e"); }
TEST(CPU_SST, BCC_Relative) { run_single_step_tests("90"); }
TEST(CPU_SST, STA_IndirectIndexed) { run_single_step_tests("91"); }
TEST(CPU_SST, STY_ZeroPageX) { run_single_step_tests("94"); }
TEST(CPU_SST, STA_ZeroPageX) { run_single_step_tests("95"); }
TEST(CPU_SST, STX_ZeroPageY) { run_single_step_tests("96"); }
TEST(CPU_SST, TYA) { run_single_step_tests("98"); }
TEST(CPU_SST, STA_AbsoluteY) { run_single_step_tests("99"); }
TEST(CPU_SST, TXS) { run_single_step_tests("9a"); }
TEST(CPU_SST, STA_AbsoluteX) { run_single_step_tests("9d"); }
TEST(CPU_SST, LDY_Immediate) { run_single_step_tests("a0"); }
TEST(CPU_SST, LDA_IndexedIndirect) { run_single_step_tests("a1"); }
TEST(CPU_SST, LDX_Immediate) { run_single_step_tests("a2"); }
TEST(CPU_SST, LDY_ZeroPage) { run_single_step_tests("a4"); }
TEST(CPU_SST, LDA_ZeroPage) { run_single_step_tests("a5"); }
TEST(CPU_SST, LDX_ZeroPage) { run_single_step_tests("a6"); }
TEST(CPU_SST, TAY) { run_single_step_tests("a8"); }
TEST(CPU_SST, LDA_Immediate) { run_single_step_tests("a9"); }
TEST(CPU_SST, TAX) { run_single_step_tests("aa"); }
TEST(CPU_SST, LDY_Absolute) { run_single_step_tests("ac"); }
TEST(CPU_SST, LDA_Absolute) { run_single_step_tests("ad"); }
TEST(CPU_SST, LDX_Absolute) { run_single_step_tests("ae"); }
TEST(CPU_SST, BCS_Relative) { run_single_step_tests("b0"); }
TEST(CPU_SST, LDA_IndirectIndexed) { run_single_step_tests("b1"); }
TEST(CPU_SST, LDY_ZeroPageX) { run_single_step_tests("b4"); }
TEST(CPU_SST, LDA_ZeroPageX) { run_single_step_tests("b5"); }
TEST(CPU_SST, LDX_ZeroPageY) { run_single_step_tests("b6"); }
TEST(CPU_SST, CLV) { run_single_step_tests("b8"); }
TEST(CPU_SST, LDA_AbsoluteY) { run_single_step_tests("b9"); }
TEST(CPU_SST, TSX) { run_single_step_tests("ba"); }
TEST(CPU_SST, LDY_AbsoluteX) { run_single_step_tests("bc"); }
TEST(CPU_SST, LDA_AbsoluteX) { run_single_step_tests("bd"); }
TEST(CPU_SST, LDX_AbsoluteY) { run_single_step_tests("be"); }
TEST(CPU_SST, CPY_Immediate) { run_single_step_tests("c0"); }
TEST(CPU_SST, CMP_IndexedIndirect) { run_single_step_tests("c1"); }
TEST(CPU_SST, CPY_ZeroPage) { run_single_step_tests("c4"); }
TEST(CPU_SST, CMP_ZeroPage) { run_single_step_tests("c5"); }
TEST(CPU_SST, DEC_ZeroPage) { run_single_step_tests("c6"); }
TEST(CPU_SST, INY) { run_single_step_tests("c8"); }
TEST(CPU_SST, CMP_Immediate) { run_single_step_tests("c9"); }
TEST(CPU_SST, DEX) { run_single_step_tests("ca"); }
TEST(CPU_SST, CPY_Absolute) { run_single_step_tests("cc"); }
TEST(CPU_SST, CMP_Absolute) { run_single_step_tests("cd"); }
TEST(CPU_SST, DEC_Absolute) { run_single_step_tests("ce"); }
TEST(CPU_SST, BNE_Relative) { run_single_step_tests("d0"); }
TEST(CPU_SST, CMP_IndirectIndexed) { run_single_step_tests("d1"); }
TEST(CPU_SST, CMP_ZeroPageX) { run_single_step_tests("d5"); }
TEST(CPU_SST, DEC_ZeroPageX) { run_single_step_tests("d6"); }
TEST(CPU_SST, CLD) { run_single_step_tests("d8"); }
TEST(CPU_SST, CMP_AbsoluteY) { run_single_step_tests("d9"); }
TEST(CPU_SST, CMP_AbsoluteX) { run_single_step_tests("dd"); }
TEST(CPU_SST, DEC_AbsoluteX) { run_single_step_tests("de"); }
TEST(CPU_SST, CPX_Immediate) { run_single_step_tests("e0"); }
TEST(CPU_SST, SBC_IndexedIndirect) { run_single_step_tests("e1"); }
TEST(CPU_SST, CPX_ZeroPage) { run_single_step_tests("e4"); }
TEST(CPU_SST, SBC_ZeroPage) { run_single_step_tests("e5"); }
TEST(CPU_SST, INC_ZeroPage) { run_single_step_tests("e6"); }
TEST(CPU_SST, INX) { run_single_step_tests("e8"); }
TEST(CPU_SST, SBC_Immediate) { run_single_step_tests("e9"); }
TEST(CPU_SST, NOP_EA) { run_single_step_tests("ea"); }
TEST(CPU_SST, CPX_Absolute) { run_single_step_tests("ec"); }
TEST(CPU_SST, SBC_Absolute) { run_single_step_tests("ed"); }
TEST(CPU_SST, INC_Absolute) { run_single_step_tests("ee"); }
TEST(CPU_SST, BEQ_Relative) { run_single_step_tests("f0"); }
TEST(CPU_SST, SBC_IndirectIndexed) { run_single_step_tests("f1"); }
TEST(CPU_SST, SBC_ZeroPageX) { run_single_step_tests("f5"); }
TEST(CPU_SST, INC_ZeroPageX) { run_single_step_tests("f6"); }
TEST(CPU_SST, SED) { run_single_step_tests("f8"); }
TEST(CPU_SST, SBC_AbsoluteY) { run_single_step_tests("f9"); }
TEST(CPU_SST, SBC_AbsoluteX) { run_single_step_tests("fd"); }
TEST(CPU_SST, INC_AbsoluteX) { run_single_step_tests("fe"); }

// Unofficial NOP OpCodes
TEST(CPU_SST, Unofficial_NOP_ZeroPage1) { run_single_step_tests("04"); }
TEST(CPU_SST, Unofficial_NOP_ZeroPage2) { run_single_step_tests("44"); }
TEST(CPU_SST, Unofficial_NOP_ZeroPage3) { run_single_step_tests("64"); }
TEST(CPU_SST, Unofficial_NOP_Absolute) { run_single_step_tests("0c"); }
TEST(CPU_SST, Unofficial_NOP_ZeroPageX1) { run_single_step_tests("14"); }
TEST(CPU_SST, Unofficial_NOP_ZeroPageX2) { run_single_step_tests("34"); }
TEST(CPU_SST, Unofficial_NOP_ZeroPageX3) { run_single_step_tests("54"); }
TEST(CPU_SST, Unofficial_NOP_ZeroPageX4) { run_single_step_tests("74"); }
TEST(CPU_SST, Unofficial_NOP_ZeroPageX5) { run_single_step_tests("d4"); }
TEST(CPU_SST, Unofficial_NOP_ZeroPageX6) { run_single_step_tests("f4"); }
TEST(CPU_SST, Unofficial_NOP_Implied1) { run_single_step_tests("1a"); }
TEST(CPU_SST, Unofficial_NOP_Implied2) { run_single_step_tests("3a"); }
TEST(CPU_SST, Unofficial_NOP_Implied3) { run_single_step_tests("5a"); }
TEST(CPU_SST, Unofficial_NOP_Implied4) { run_single_step_tests("7a"); }
TEST(CPU_SST, Unofficial_NOP_Implied5) { run_single_step_tests("da"); }
TEST(CPU_SST, Unofficial_NOP_Implied6) { run_single_step_tests("fa"); }
TEST(CPU_SST, Unofficial_NOP_Immediate1) { run_single_step_tests("80"); }
TEST(CPU_SST, Unofficial_NOP_Immediate2) { run_single_step_tests("82"); }
TEST(CPU_SST, Unofficial_NOP_Immediate3) { run_single_step_tests("89"); }
TEST(CPU_SST, Unofficial_NOP_Immediate4) { run_single_step_tests("c2"); }
TEST(CPU_SST, Unofficial_NOP_Immediate5) { run_single_step_tests("e2"); }
TEST(CPU_SST, Unofficial_NOP_AbsoluteX1) { run_single_step_tests("1c"); }
TEST(CPU_SST, Unofficial_NOP_AbsoluteX2) { run_single_step_tests("3c"); }
TEST(CPU_SST, Unofficial_NOP_AbsoluteX3) { run_single_step_tests("5c"); }
TEST(CPU_SST, Unofficial_NOP_AbsoluteX4) { run_single_step_tests("7c"); }
TEST(CPU_SST, Unofficial_NOP_AbsoluteX5) { run_single_step_tests("dc"); }
TEST(CPU_SST, Unofficial_NOP_AbsoluteX6) { run_single_step_tests("fc"); }

TEST(CPU_SST, Unofficial_KIL) { run_single_step_tests("02"); }
TEST(CPU_SST, Unofficial_SLO_IndexedIndirect) { run_single_step_tests("03"); }
TEST(CPU_SST, Unofficial_SLO_ZeroPage) { run_single_step_tests("07"); }
TEST(CPU_SST, Unofficial_ANC_Immediate) { run_single_step_tests("0b"); }
TEST(CPU_SST, Unofficial_SLO_Absolute) { run_single_step_tests("0f"); }
TEST(CPU_SST, Unofficial_KIL_12) { run_single_step_tests("12"); }
TEST(CPU_SST, Unofficial_SLO_IndirectIndexed) { run_single_step_tests("13"); }
TEST(CPU_SST, Unofficial_SLO_ZeroPageX) { run_single_step_tests("17"); }
TEST(CPU_SST, Unofficial_SLO_AbsoluteY) { run_single_step_tests("1b"); }
TEST(CPU_SST, Unofficial_SLO_AbsoluteX) { run_single_step_tests("1f"); }
TEST(CPU_SST, Unofficial_KIL_22) { run_single_step_tests("22"); }
TEST(CPU_SST, Unofficial_RLA_IndexedIndirect) { run_single_step_tests("23"); }
TEST(CPU_SST, Unofficial_RLA_ZeroPage) { run_single_step_tests("27"); }
TEST(CPU_SST, Unofficial_ANC_Immediate_2B) { run_single_step_tests("2b"); }
TEST(CPU_SST, Unofficial_RLA_Absolute) { run_single_step_tests("2f"); }
TEST(CPU_SST, Unofficial_KIL_32) { run_single_step_tests("32"); }
TEST(CPU_SST, Unofficial_RLA_IndirectIndexed) { run_single_step_tests("33"); }
TEST(CPU_SST, Unofficial_RLA_ZeroPageX) { run_single_step_tests("37"); }
TEST(CPU_SST, Unofficial_RLA_AbsoluteY) { run_single_step_tests("3b"); }
TEST(CPU_SST, Unofficial_RLA_AbsoluteX) { run_single_step_tests("3f"); }
TEST(CPU_SST, Unofficial_KIL_42) { run_single_step_tests("42"); }
TEST(CPU_SST, Unofficial_SRE_IndexedIndirect) { run_single_step_tests("43"); }
TEST(CPU_SST, Unofficial_SRE_ZeroPage) { run_single_step_tests("47"); }
TEST(CPU_SST, Unofficial_ALR_Immediate) { run_single_step_tests("4b"); }
TEST(CPU_SST, Unofficial_SRE_Absolute) { run_single_step_tests("4f"); }
TEST(CPU_SST, Unofficial_KIL_52) { run_single_step_tests("52"); }
TEST(CPU_SST, Unofficial_SRE_IndirectIndexed) { run_single_step_tests("53"); }
TEST(CPU_SST, Unofficial_SRE_ZeroPageX) { run_single_step_tests("57"); }
TEST(CPU_SST, Unofficial_SRE_AbsoluteY) { run_single_step_tests("5b"); }
TEST(CPU_SST, Unofficial_SRE_AbsoluteX) { run_single_step_tests("5f"); }
TEST(CPU_SST, Unofficial_KIL_62) { run_single_step_tests("62"); }
TEST(CPU_SST, Unofficial_RRA_IndexedIndirect) { run_single_step_tests("63"); }
TEST(CPU_SST, Unofficial_RRA_ZeroPage) { run_single_step_tests("67"); }
TEST(CPU_SST, Unofficial_ARR_Immediate) { run_single_step_tests("6b"); }
TEST(CPU_SST, Unofficial_RRA_Absolute) { run_single_step_tests("6f"); }
TEST(CPU_SST, Unofficial_KIL_72) { run_single_step_tests("72"); }
TEST(CPU_SST, Unofficial_RRA_IndirectIndexed) { run_single_step_tests("73"); }
TEST(CPU_SST, Unofficial_RRA_ZeroPageX) { run_single_step_tests("77"); }
TEST(CPU_SST, Unofficial_RRA_AbsoluteY) { run_single_step_tests("7b"); }
TEST(CPU_SST, Unofficial_RRA_AbsoluteX) { run_single_step_tests("7f"); }
TEST(CPU_SST, Unofficial_SAX_IndexedIndirect) { run_single_step_tests("83"); }
TEST(CPU_SST, Unofficial_SAX_ZeroPage) { run_single_step_tests("87"); }
TEST(CPU_SST, Unofficial_XAA_Immediate) { run_single_step_tests("8b"); }
TEST(CPU_SST, Unofficial_SAX_Absolute) { run_single_step_tests("8f"); }
TEST(CPU_SST, Unofficial_KIL_92) { run_single_step_tests("92"); }
TEST(CPU_SST, Unofficial_AHX_IndirectIndexed) { run_single_step_tests("93"); }
TEST(CPU_SST, Unofficial_SAX_ZeroPageY) { run_single_step_tests("97"); }
TEST(CPU_SST, Unofficial_TAS_AbsoluteY) { run_single_step_tests("9b"); }
TEST(CPU_SST, Unofficial_SHY_AbsoluteX) { run_single_step_tests("9c"); }
TEST(CPU_SST, Unofficial_SHX_AbsoluteY) { run_single_step_tests("9e"); }
TEST(CPU_SST, Unofficial_AHX_AbsoluteY) { run_single_step_tests("9f"); }
TEST(CPU_SST, Unofficial_LAX_IndexedIndirect) { run_single_step_tests("a3"); }
TEST(CPU_SST, Unofficial_LAX_ZeroPage) { run_single_step_tests("a7"); }
TEST(CPU_SST, Unofficial_LAX_Immediate) { run_single_step_tests("ab"); }
TEST(CPU_SST, Unofficial_LAX_Absolute) { run_single_step_tests("af"); }
TEST(CPU_SST, Unofficial_KIL_B2) { run_single_step_tests("b2"); }
TEST(CPU_SST, Unofficial_LAX_IndirectIndexed) { run_single_step_tests("b3"); }
TEST(CPU_SST, Unofficial_LAX_ZeroPageY) { run_single_step_tests("b7"); }
TEST(CPU_SST, Unofficial_LAS_AbsoluteY) { run_single_step_tests("bb"); }
TEST(CPU_SST, Unofficial_LAX_AbsoluteY) { run_single_step_tests("bf"); }
TEST(CPU_SST, Unofficial_DCP_IndexedIndirect) { run_single_step_tests("c3"); }
TEST(CPU_SST, Unofficial_DCP_ZeroPage) { run_single_step_tests("c7"); }
TEST(CPU_SST, Unofficial_AXS_Immediate) { run_single_step_tests("cb"); }
TEST(CPU_SST, Unofficial_DCP_Absolute) { run_single_step_tests("cf"); }
TEST(CPU_SST, Unofficial_KIL_D2) { run_single_step_tests("d2"); }
TEST(CPU_SST, Unofficial_DCP_IndirectIndexed) { run_single_step_tests("d3"); }
TEST(CPU_SST, Unofficial_DCP_ZeroPageX) { run_single_step_tests("d7"); }
TEST(CPU_SST, Unofficial_DCP_AbsoluteY) { run_single_step_tests("db"); }
TEST(CPU_SST, Unofficial_DCP_AbsoluteX) { run_single_step_tests("df"); }
TEST(CPU_SST, Unofficial_ISC_IndexedIndirect) { run_single_step_tests("e3"); }
TEST(CPU_SST, Unofficial_ISC_ZeroPage) { run_single_step_tests("e7"); }
TEST(CPU_SST, Unofficial_SBC_Immediate_EB) { run_single_step_tests("eb"); }
TEST(CPU_SST, Unofficial_ISC_Absolute) { run_single_step_tests("ef"); }
TEST(CPU_SST, Unofficial_KIL_F2) { run_single_step_tests("f2"); }
TEST(CPU_SST, Unofficial_ISC_IndirectIndexed) { run_single_step_tests("f3"); }
TEST(CPU_SST, Unofficial_ISC_ZeroPageX) { run_single_step_tests("f7"); }
TEST(CPU_SST, Unofficial_ISC_AbsoluteY) { run_single_step_tests("fb"); }
TEST(CPU_SST, Unofficial_ISC_AbsoluteX) { run_single_step_tests("ff"); }
