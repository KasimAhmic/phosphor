# Phosphor

My attempt at making an NES emulator from scratch using C++ and SDL3.

## Progress

- CPU emulation:
  - Status: **In progress**
  - Official opcodes implemented: 151/151
  - Unofficial opcodes implemented: 27/105
- PPU emulation:
  - Status: **Not started**
- APU emulation:
  - Status: **Not started**
- Input handling:
  - Status: **Not started**
- ROM loading:
  - Status: **Not started**

## Build Instructions

```bash
git clone https://github.com/KasimAhmic/phosphor.git --recursive

cd phosphor

cmake -S . -B build
cmake --build build
```
