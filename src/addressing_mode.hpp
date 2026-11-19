#pragma once

#include <cstdint>

enum class AddressingMode : std::uint8_t {
  Implied,
  Accumulator,
  Immediate,
  Relative,
  ZeroPage,
  ZeroPageX,
  ZeroPageY,
  Absolute,
  AbsoluteX,
  AbsoluteY,
  Indirect,
  IndexedIndirect,
  IndirectIndexed,
};
