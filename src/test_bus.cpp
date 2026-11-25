#include "test_bus.hpp"

TestBus::TestBus()
    : _memory{} {}

TestBus::~TestBus() = default;

std::uint8_t TestBus::read(std::uint16_t addr) { return this->_memory[addr]; }

void TestBus::write(std::uint16_t addr, std::uint8_t value) { this->_memory[addr] = value; }
