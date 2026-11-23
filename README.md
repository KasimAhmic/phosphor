# Phosphor

My attempt at making an NES emulator from scratch using C++ and SDL3.

## Progress

- CPU emulation: In progress
  - 83/151 official 6502 opcodes implemented
  - 0/105 unofficial 6502 opcodes implemented
- PPU emulation: Not started
- APU emulation: Not started
- Input handling: Not started
- ROM loading: Not started

## Build Instructions

```bash
git clone https://github.com/KasimAhmic/phosphor.git --recursive

cd phosphor

cmake -S . -B build
cmake --build build
```
