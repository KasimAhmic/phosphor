# Phosphor

My attempt at making an NES emulator from scratch using C++ and SDL3.

## Progress

- CPU emulation:
  - Status: **DONE!**
  - Official opcodes implemented: 151/151
  - Unofficial opcodes implemented: 105/105
- PPU emulation:
  - Status: **In progress**
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
