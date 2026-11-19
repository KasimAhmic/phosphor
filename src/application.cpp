#include "application.hpp"

#include <spdlog/spdlog.h>

Application::Application() : window(nullptr), renderer(nullptr) {}

Application::~Application() {
  if (this->renderer) {
    SDL_DestroyRenderer(this->renderer);
  }

  if (this->window) {
    SDL_DestroyWindow(this->window);
  }
}

void Application::init() {
  if (this->window = SDL_CreateWindow("Phosphor", 1600, 900, SDL_WINDOW_HIDDEN); !this->window) {
    throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
  }

  if (this->renderer = SDL_CreateRenderer(this->window, nullptr); !this->renderer) {
    throw std::runtime_error("Failed to create SDL renderer: " + std::string(SDL_GetError()));
  }

  if (!SDL_SetRenderVSync(this->renderer, 1)) {
    spdlog::warn("Failed to enable VSync: {}", SDL_GetError());
  }

  if (!SDL_ShowWindow(this->window)) {
    spdlog::warn("Failed to show window: {}", SDL_GetError());
  }
}

void Application::update(const double delta_time) {}

void Application::render() {
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
  SDL_RenderClear(this->renderer);

  SDL_RenderPresent(this->renderer);
}

SDL_AppResult Application::handle_event(const SDL_Event& event) {
  switch (event.type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;

  default:
    return SDL_APP_CONTINUE;
  }
}
