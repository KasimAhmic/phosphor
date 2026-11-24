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

void run_single_step_tests(std::string filename) {
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

TEST(CPU, SST_BRK) { run_single_step_tests("00"); }
TEST(CPU, SST_ORA_IndexedIndirect) { run_single_step_tests("01"); }
TEST(CPU, SST_ORA_ZeroPage) { run_single_step_tests("05"); }
TEST(CPU, SST_ASL_ZeroPage) { run_single_step_tests("06"); }
TEST(CPU, SST_PHP) { run_single_step_tests("08"); }
TEST(CPU, SST_ORA_Immediate) { run_single_step_tests("09"); }
TEST(CPU, SST_ASL_Accumulator) { run_single_step_tests("0a"); }
TEST(CPU, SST_ORA_Absolute) { run_single_step_tests("0d"); }
TEST(CPU, SST_ASL_Absolute) { run_single_step_tests("0e"); }
TEST(CPU, SST_BPL_Relative) { run_single_step_tests("10"); }
TEST(CPU, SST_ORA_IndirectIndexed) { run_single_step_tests("11"); }
TEST(CPU, SST_ORA_ZeroPageX) { run_single_step_tests("15"); }
TEST(CPU, SST_ASL_ZeroPageX) { run_single_step_tests("16"); }
TEST(CPU, SST_CLC) { run_single_step_tests("18"); }
TEST(CPU, SST_ORA_AbsoluteY) { run_single_step_tests("19"); }
TEST(CPU, SST_ORA_AbsoluteX) { run_single_step_tests("1d"); }
TEST(CPU, SST_ASL_AbsoluteX) { run_single_step_tests("1e"); }
TEST(CPU, SST_JSR_Absolute) { run_single_step_tests("20"); }
TEST(CPU, SST_AND_IndexedIndirect) { run_single_step_tests("21"); }
TEST(CPU, SST_BIT_ZeroPage) { run_single_step_tests("24"); }
TEST(CPU, SST_AND_ZeroPage) { run_single_step_tests("25"); }
TEST(CPU, SST_ROL_ZeroPage) { run_single_step_tests("26"); }
TEST(CPU, SST_PLP) { run_single_step_tests("28"); }
TEST(CPU, SST_AND_Immediate) { run_single_step_tests("29"); }
TEST(CPU, SST_ROL_Accumulator) { run_single_step_tests("2a"); }
TEST(CPU, SST_BIT_Absolute) { run_single_step_tests("2c"); }
TEST(CPU, SST_AND_Absolute) { run_single_step_tests("2d"); }
TEST(CPU, SST_ROL_Absolute) { run_single_step_tests("2e"); }
TEST(CPU, SST_BMI_Relative) { run_single_step_tests("30"); }
TEST(CPU, SST_AND_IndirectIndexed) { run_single_step_tests("31"); }
TEST(CPU, SST_AND_ZeroPageX) { run_single_step_tests("35"); }
TEST(CPU, SST_ROL_ZeroPageX) { run_single_step_tests("36"); }
TEST(CPU, SST_SEC) { run_single_step_tests("38"); }
TEST(CPU, SST_AND_AbsoluteY) { run_single_step_tests("39"); }
TEST(CPU, SST_AND_AbsoluteX) { run_single_step_tests("3d"); }
TEST(CPU, SST_ROL_AbsoluteX) { run_single_step_tests("3e"); }
TEST(CPU, SST_RTI) { run_single_step_tests("40"); }
TEST(CPU, SST_EOR_IndexedIndirect) { run_single_step_tests("41"); }
TEST(CPU, SST_EOR_ZeroPage) { run_single_step_tests("45"); }
TEST(CPU, SST_LSR_ZeroPage) { run_single_step_tests("46"); }
TEST(CPU, SST_PHA) { run_single_step_tests("48"); }
TEST(CPU, SST_EOR_Immediate) { run_single_step_tests("49"); }
TEST(CPU, SST_LSR_Accumulator) { run_single_step_tests("4a"); }
TEST(CPU, SST_JMP_Absolute) { run_single_step_tests("4c"); }
TEST(CPU, SST_EOR_Absolute) { run_single_step_tests("4d"); }
TEST(CPU, SST_LSR_Absolute) { run_single_step_tests("4e"); }
TEST(CPU, SST_BVC_Relative) { run_single_step_tests("50"); }
TEST(CPU, SST_EOR_IndirectIndexed) { run_single_step_tests("51"); }
TEST(CPU, SST_EOR_ZeroPageX) { run_single_step_tests("55"); }
TEST(CPU, SST_LSR_ZeroPageX) { run_single_step_tests("56"); }
TEST(CPU, SST_CLI) { run_single_step_tests("58"); }
TEST(CPU, SST_EOR_AbsoluteY) { run_single_step_tests("59"); }
TEST(CPU, SST_EOR_AbsoluteX) { run_single_step_tests("5d"); }
TEST(CPU, SST_LSR_AbsoluteX) { run_single_step_tests("5e"); }
TEST(CPU, SST_RTS) { run_single_step_tests("60"); }
TEST(CPU, SST_ADC_IndexedIndirect) { run_single_step_tests("61"); }
TEST(CPU, SST_ADC_ZeroPage) { run_single_step_tests("65"); }
TEST(CPU, SST_ROR_ZeroPage) { run_single_step_tests("66"); }
TEST(CPU, SST_PLA) { run_single_step_tests("68"); }
TEST(CPU, SST_ADC_Immediate) { run_single_step_tests("69"); }
TEST(CPU, SST_ROR_Accumulator) { run_single_step_tests("6a"); }
TEST(CPU, SST_JMP_Indirect) { run_single_step_tests("6c"); }
TEST(CPU, SST_ADC_Absolute) { run_single_step_tests("6d"); }
TEST(CPU, SST_ROR_Absolute) { run_single_step_tests("6e"); }
TEST(CPU, SST_BVS_Relative) { run_single_step_tests("70"); }
TEST(CPU, SST_ADC_IndirectIndexed) { run_single_step_tests("71"); }
TEST(CPU, SST_ADC_ZeroPageX) { run_single_step_tests("75"); }
TEST(CPU, SST_ROR_ZeroPageX) { run_single_step_tests("76"); }
TEST(CPU, SST_SEI) { run_single_step_tests("78"); }
TEST(CPU, SST_ADC_AbsoluteY) { run_single_step_tests("79"); }
TEST(CPU, SST_ADC_AbsoluteX) { run_single_step_tests("7d"); }
TEST(CPU, SST_ROR_AbsoluteX) { run_single_step_tests("7e"); }
TEST(CPU, SST_STA_IndexedIndirect) { run_single_step_tests("81"); }
TEST(CPU, SST_STY_ZeroPage) { run_single_step_tests("84"); }
TEST(CPU, SST_STA_ZeroPage) { run_single_step_tests("85"); }
TEST(CPU, SST_STX_ZeroPage) { run_single_step_tests("86"); }
TEST(CPU, SST_DEY) { run_single_step_tests("88"); }
TEST(CPU, SST_TXA) { run_single_step_tests("8a"); }
TEST(CPU, SST_STY_Absolute) { run_single_step_tests("8c"); }
TEST(CPU, SST_STA_Absolute) { run_single_step_tests("8d"); }
TEST(CPU, SST_STX_Absolute) { run_single_step_tests("8e"); }
TEST(CPU, SST_BCC_Relative) { run_single_step_tests("90"); }
TEST(CPU, SST_STA_IndirectIndexed) { run_single_step_tests("91"); }
TEST(CPU, SST_STY_ZeroPageX) { run_single_step_tests("94"); }
TEST(CPU, SST_STA_ZeroPageX) { run_single_step_tests("95"); }
TEST(CPU, SST_STX_ZeroPageY) { run_single_step_tests("96"); }
TEST(CPU, SST_TYA) { run_single_step_tests("98"); }
TEST(CPU, SST_STA_AbsoluteY) { run_single_step_tests("99"); }
TEST(CPU, SST_TXS) { run_single_step_tests("9a"); }
TEST(CPU, SST_STA_AbsoluteX) { run_single_step_tests("9d"); }
TEST(CPU, SST_LDY_Immediate) { run_single_step_tests("a0"); }
TEST(CPU, SST_LDA_IndexedIndirect) { run_single_step_tests("a1"); }
TEST(CPU, SST_LDX_Immediate) { run_single_step_tests("a2"); }
TEST(CPU, SST_LDY_ZeroPage) { run_single_step_tests("a4"); }
TEST(CPU, SST_LDA_ZeroPage) { run_single_step_tests("a5"); }
TEST(CPU, SST_LDX_ZeroPage) { run_single_step_tests("a6"); }
TEST(CPU, SST_TAY) { run_single_step_tests("a8"); }
TEST(CPU, SST_LDA_Immediate) { run_single_step_tests("a9"); }
TEST(CPU, SST_TAX) { run_single_step_tests("aa"); }
TEST(CPU, SST_LDY_Absolute) { run_single_step_tests("ac"); }
TEST(CPU, SST_LDA_Absolute) { run_single_step_tests("ad"); }
TEST(CPU, SST_LDX_Absolute) { run_single_step_tests("ae"); }
TEST(CPU, SST_BCS_Relative) { run_single_step_tests("b0"); }
TEST(CPU, SST_LDA_IndirectIndexed) { run_single_step_tests("b1"); }
TEST(CPU, SST_LDY_ZeroPageX) { run_single_step_tests("b4"); }
TEST(CPU, SST_LDA_ZeroPageX) { run_single_step_tests("b5"); }
TEST(CPU, SST_LDX_ZeroPageY) { run_single_step_tests("b6"); }
TEST(CPU, SST_CLV) { run_single_step_tests("b8"); }
TEST(CPU, SST_LDA_AbsoluteY) { run_single_step_tests("b9"); }
TEST(CPU, SST_TSX) { run_single_step_tests("ba"); }
TEST(CPU, SST_LDY_AbsoluteX) { run_single_step_tests("bc"); }
TEST(CPU, SST_LDA_AbsoluteX) { run_single_step_tests("bd"); }
TEST(CPU, SST_LDX_AbsoluteY) { run_single_step_tests("be"); }
TEST(CPU, SST_CPY_Immediate) { run_single_step_tests("c0"); }
TEST(CPU, SST_CMP_IndexedIndirect) { run_single_step_tests("c1"); }
TEST(CPU, SST_CPY_ZeroPage) { run_single_step_tests("c4"); }
TEST(CPU, SST_CMP_ZeroPage) { run_single_step_tests("c5"); }
TEST(CPU, SST_DEC_ZeroPage) { run_single_step_tests("c6"); }
TEST(CPU, SST_INY) { run_single_step_tests("c8"); }
TEST(CPU, SST_CMP_Immediate) { run_single_step_tests("c9"); }
TEST(CPU, SST_DEX) { run_single_step_tests("ca"); }
TEST(CPU, SST_CPY_Absolute) { run_single_step_tests("cc"); }
TEST(CPU, SST_CMP_Absolute) { run_single_step_tests("cd"); }
TEST(CPU, SST_DEC_Absolute) { run_single_step_tests("ce"); }
TEST(CPU, SST_BNE_Relative) { run_single_step_tests("d0"); }
TEST(CPU, SST_CMP_IndirectIndexed) { run_single_step_tests("d1"); }
TEST(CPU, SST_CMP_ZeroPageX) { run_single_step_tests("d5"); }
TEST(CPU, SST_DEC_ZeroPageX) { run_single_step_tests("d6"); }
TEST(CPU, SST_CLD) { run_single_step_tests("d8"); }
TEST(CPU, SST_CMP_AbsoluteY) { run_single_step_tests("d9"); }
TEST(CPU, SST_CMP_AbsoluteX) { run_single_step_tests("dd"); }
TEST(CPU, SST_DEC_AbsoluteX) { run_single_step_tests("de"); }
TEST(CPU, SST_CPX_Immediate) { run_single_step_tests("e0"); }
TEST(CPU, SST_SBC_IndexedIndirect) { run_single_step_tests("e1"); }
TEST(CPU, SST_CPX_ZeroPage) { run_single_step_tests("e4"); }
TEST(CPU, SST_SBC_ZeroPage) { run_single_step_tests("e5"); }
TEST(CPU, SST_INC_ZeroPage) { run_single_step_tests("e6"); }
TEST(CPU, SST_INX) { run_single_step_tests("e8"); }
TEST(CPU, SST_SBC_Immediate) { run_single_step_tests("e9"); }
TEST(CPU, SST_NOP_EA) { run_single_step_tests("ea"); }
TEST(CPU, SST_CPX_Absolute) { run_single_step_tests("ec"); }
TEST(CPU, SST_SBC_Absolute) { run_single_step_tests("ed"); }
TEST(CPU, SST_INC_Absolute) { run_single_step_tests("ee"); }
TEST(CPU, SST_BEQ_Relative) { run_single_step_tests("f0"); }
TEST(CPU, SST_SBC_IndirectIndexed) { run_single_step_tests("f1"); }
TEST(CPU, SST_SBC_ZeroPageX) { run_single_step_tests("f5"); }
TEST(CPU, SST_INC_ZeroPageX) { run_single_step_tests("f6"); }
TEST(CPU, SST_SED) { run_single_step_tests("f8"); }
TEST(CPU, SST_SBC_AbsoluteY) { run_single_step_tests("f9"); }
TEST(CPU, SST_SBC_AbsoluteX) { run_single_step_tests("fd"); }
TEST(CPU, SST_INC_AbsoluteX) { run_single_step_tests("fe"); }

// TEST(CPU, SST_KIL) { run_single_step_tests("02"); }
// TEST(CPU, SST_SLO_IndexedIndirect) { run_single_step_tests("03"); }
// TEST(CPU, SST_NOP_ZeroPage) { run_single_step_tests("04"); }
// TEST(CPU, SST_SLO_ZeroPage) { run_single_step_tests("07"); }
// TEST(CPU, SST_ANC_Immediate) { run_single_step_tests("0b"); }
// TEST(CPU, SST_NOP_Absolute) { run_single_step_tests("0c"); }
// TEST(CPU, SST_SLO_Absolute) { run_single_step_tests("0f"); }
// TEST(CPU, SST_KIL_12) { run_single_step_tests("12"); }
// TEST(CPU, SST_SLO_IndirectIndexed) { run_single_step_tests("13"); }
// TEST(CPU, SST_NOP_ZeroPageX) { run_single_step_tests("14"); }
// TEST(CPU, SST_SLO_ZeroPageX) { run_single_step_tests("17"); }
// TEST(CPU, SST_NOP) { run_single_step_tests("1a"); }
// TEST(CPU, SST_SLO_AbsoluteY) { run_single_step_tests("1b"); }
// TEST(CPU, SST_NOP_AbsoluteX) { run_single_step_tests("1c"); }
// TEST(CPU, SST_SLO_AbsoluteX) { run_single_step_tests("1f"); }
// TEST(CPU, SST_KIL_22) { run_single_step_tests("22"); }
// TEST(CPU, SST_RLA_IndexedIndirect) { run_single_step_tests("23"); }
// TEST(CPU, SST_RLA_ZeroPage) { run_single_step_tests("27"); }
// TEST(CPU, SST_ANC_Immediate_2B) { run_single_step_tests("2b"); }
// TEST(CPU, SST_RLA_Absolute) { run_single_step_tests("2f"); }
// TEST(CPU, SST_KIL_32) { run_single_step_tests("32"); }
// TEST(CPU, SST_RLA_IndirectIndexed) { run_single_step_tests("33"); }
// TEST(CPU, SST_NOP_ZeroPageX_34) { run_single_step_tests("34"); }
// TEST(CPU, SST_RLA_ZeroPageX) { run_single_step_tests("37"); }
// TEST(CPU, SST_NOP_3A) { run_single_step_tests("3a"); }
// TEST(CPU, SST_RLA_AbsoluteY) { run_single_step_tests("3b"); }
// TEST(CPU, SST_NOP_AbsoluteX_3C) { run_single_step_tests("3c"); }
// TEST(CPU, SST_RLA_AbsoluteX) { run_single_step_tests("3f"); }
// TEST(CPU, SST_KIL_42) { run_single_step_tests("42"); }
// TEST(CPU, SST_SRE_IndexedIndirect) { run_single_step_tests("43"); }
// TEST(CPU, SST_NOP_ZeroPage_44) { run_single_step_tests("44"); }
// TEST(CPU, SST_SRE_ZeroPage) { run_single_step_tests("47"); }
// TEST(CPU, SST_ALR_Immediate) { run_single_step_tests("4b"); }
// TEST(CPU, SST_SRE_Absolute) { run_single_step_tests("4f"); }
// TEST(CPU, SST_KIL_52) { run_single_step_tests("52"); }
// TEST(CPU, SST_SRE_IndirectIndexed) { run_single_step_tests("53"); }
// TEST(CPU, SST_NOP_ZeroPageX_54) { run_single_step_tests("54"); }
// TEST(CPU, SST_SRE_ZeroPageX) { run_single_step_tests("57"); }
// TEST(CPU, SST_NOP_5A) { run_single_step_tests("5a"); }
// TEST(CPU, SST_SRE_AbsoluteY) { run_single_step_tests("5b"); }
// TEST(CPU, SST_NOP_AbsoluteX_5C) { run_single_step_tests("5c"); }
// TEST(CPU, SST_SRE_AbsoluteX) { run_single_step_tests("5f"); }
// TEST(CPU, SST_KIL_62) { run_single_step_tests("62"); }
// TEST(CPU, SST_RRA_IndexedIndirect) { run_single_step_tests("63"); }
// TEST(CPU, SST_NOP_ZeroPage_64) { run_single_step_tests("64"); }
// TEST(CPU, SST_RRA_ZeroPage) { run_single_step_tests("67"); }
// TEST(CPU, SST_ARR_Immediate) { run_single_step_tests("6b"); }
// TEST(CPU, SST_RRA_Absolute) { run_single_step_tests("6f"); }
// TEST(CPU, SST_KIL_72) { run_single_step_tests("72"); }
// TEST(CPU, SST_RRA_IndirectIndexed) { run_single_step_tests("73"); }
// TEST(CPU, SST_NOP_ZeroPageX_74) { run_single_step_tests("74"); }
// TEST(CPU, SST_RRA_ZeroPageX) { run_single_step_tests("77"); }
// TEST(CPU, SST_NOP_7a) { run_single_step_tests("7a"); }
// TEST(CPU, SST_RRA_AbsoluteY) { run_single_step_tests("7b"); }
// TEST(CPU, SST_NOP_AbsoluteX_7c) { run_single_step_tests("7c"); }
// TEST(CPU, SST_RRA_AbsoluteX) { run_single_step_tests("7f"); }
// TEST(CPU, SST_NOP_Immediate) { run_single_step_tests("80"); }
// TEST(CPU, SST_NOP_Immediate_82) { run_single_step_tests("82"); }
// TEST(CPU, SST_SAX_IndexedIndirect) { run_single_step_tests("83"); }
// TEST(CPU, SST_SAX_ZeroPage) { run_single_step_tests("87"); }
// TEST(CPU, SST_NOP_Immediate_89) { run_single_step_tests("89"); }
// TEST(CPU, SST_XAA_Immediate) { run_single_step_tests("8b"); }
// TEST(CPU, SST_SAX_Absolute) { run_single_step_tests("8f"); }
// TEST(CPU, SST_KIL_92) { run_single_step_tests("92"); }
// TEST(CPU, SST_AHX_IndirectIndexed) { run_single_step_tests("93"); }
// TEST(CPU, SST_SAX_ZeroPageY) { run_single_step_tests("97"); }
// TEST(CPU, SST_TAS_AbsoluteY) { run_single_step_tests("9b"); }
// TEST(CPU, SST_SHY_AbsoluteX) { run_single_step_tests("9c"); }
// TEST(CPU, SST_SHX_AbsoluteY) { run_single_step_tests("9e"); }
// TEST(CPU, SST_AHX_AbsoluteY) { run_single_step_tests("9f"); }
// TEST(CPU, SST_LAX_IndexedIndirect) { run_single_step_tests("a3"); }
// TEST(CPU, SST_LAX_ZeroPage) { run_single_step_tests("a7"); }
// TEST(CPU, SST_LAX_Immediate) { run_single_step_tests("ab"); }
// TEST(CPU, SST_LAX_Absolute) { run_single_step_tests("af"); }
// TEST(CPU, SST_KIL_B2) { run_single_step_tests("b2"); }
// TEST(CPU, SST_LAX_IndirectIndexed) { run_single_step_tests("b3"); }
// TEST(CPU, SST_LAX_ZeroPageY) { run_single_step_tests("b7"); }
// TEST(CPU, SST_LAS_AbsoluteY) { run_single_step_tests("bb"); }
// TEST(CPU, SST_LAX_AbsoluteY) { run_single_step_tests("bf"); }
// TEST(CPU, SST_NOP_Immediate_C2) { run_single_step_tests("c2"); }
// TEST(CPU, SST_DCP_IndexedIndirect) { run_single_step_tests("c3"); }
// TEST(CPU, SST_DCP_ZeroPage) { run_single_step_tests("c7"); }
// TEST(CPU, SST_AXS_Immediate) { run_single_step_tests("cb"); }
// TEST(CPU, SST_DCP_Absolute) { run_single_step_tests("cf"); }
// TEST(CPU, SST_KIL_D2) { run_single_step_tests("d2"); }
// TEST(CPU, SST_DCP_IndirectIndexed) { run_single_step_tests("d3"); }
// TEST(CPU, SST_NOP_ZeroPageX_D4) { run_single_step_tests("d4"); }
// TEST(CPU, SST_DCP_ZeroPageX) { run_single_step_tests("d7"); }
// TEST(CPU, SST_NOP_DA) { run_single_step_tests("da"); }
// TEST(CPU, SST_DCP_AbsoluteY) { run_single_step_tests("db"); }
// TEST(CPU, SST_NOP_AbsoluteX_DC) { run_single_step_tests("dc"); }
// TEST(CPU, SST_DCP_AbsoluteX) { run_single_step_tests("df"); }
// TEST(CPU, SST_NOP_Immediate_E2) { run_single_step_tests("e2"); }
// TEST(CPU, SST_ISC_IndexedIndirect) { run_single_step_tests("e3"); }
// TEST(CPU, SST_ISC_ZeroPage) { run_single_step_tests("e7"); }
// TEST(CPU, SST_SBC_Immediate_EB) { run_single_step_tests("eb"); }
// TEST(CPU, SST_ISC_Absolute) { run_single_step_tests("ef"); }
// TEST(CPU, SST_KIL_F2) { run_single_step_tests("f2"); }
// TEST(CPU, SST_ISC_IndirectIndexed) { run_single_step_tests("f3"); }
// TEST(CPU, SST_NOP_ZeroPageX_F4) { run_single_step_tests("f4"); }
// TEST(CPU, SST_ISC_ZeroPageX) { run_single_step_tests("f7"); }
// TEST(CPU, SST_NOP_FA) { run_single_step_tests("fa"); }
// TEST(CPU, SST_ISC_AbsoluteY) { run_single_step_tests("fb"); }
// TEST(CPU, SST_NOP_AbsoluteX_FC) { run_single_step_tests("fc"); }
// TEST(CPU, SST_ISC_AbsoluteX) { run_single_step_tests("ff"); }
