#include "application.hpp"

#include <spdlog/spdlog.h>

Application::Application()
    : _window(nullptr),
      _renderer(nullptr),
      _nes() {}

Application::~Application() {
  if (this->_renderer) {
    SDL_DestroyRenderer(this->_renderer);
  }

  if (this->_window) {
    SDL_DestroyWindow(this->_window);
  }
}

void Application::init() {
  if (this->_window = SDL_CreateWindow("Phosphor", 1600, 900, SDL_WINDOW_HIDDEN); !this->_window) {
    throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
  }

  if (this->_renderer = SDL_CreateRenderer(this->_window, nullptr); !this->_renderer) {
    throw std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
  }

  if (!SDL_SetRenderVSync(this->_renderer, 1)) {
    spdlog::warn("Failed to enable VSync: {}", SDL_GetError());
  }

  if (!SDL_ShowWindow(this->_window)) {
    spdlog::warn("Failed to show window: {}", SDL_GetError());
  }
}

void Application::update(const double delta_time) {}

void Application::render() {
  SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 255);
  SDL_RenderClear(this->_renderer);

  SDL_RenderPresent(this->_renderer);
}

SDL_AppResult Application::handle_event(const SDL_Event& event) {
  switch (event.type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;

  default:
    return SDL_APP_CONTINUE;
  }
}
