#include "nes.hpp"

NES::NES()
    : _ppu{},
      _apu{},
      _cartridge{},
      _controller1{},
      _controller2{},
      _bus{
          _ppu,
          _apu,
          _cartridge,
          _controller1,
          _controller2,
      },
      _cpu{_bus} {}

NES::~NES() = default;
