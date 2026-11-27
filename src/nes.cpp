#include "nes.hpp"

NES::NES()
    : ppu_{},
      apu_{},
      cartridge_{},
      controller1_{},
      controller2_{},
      bus_{
          this->ppu_,
          this->apu_,
          this->cartridge_,
          this->controller1_,
          this->controller2_,
      },
      cpu_{bus_} {}

NES::~NES() = default;
