#pragma once

#include <cstdint>

class Controller {
public:
  explicit Controller();
  ~Controller();

  [[nodiscard]] std::uint8_t read();
};
