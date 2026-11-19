#pragma once

#include <SDL3/SDL.h>

class Application {
public:
  explicit Application();
  ~Application();

  void init();
  void update(double delta_time);
  void render();
  SDL_AppResult handle_event(const SDL_Event& event);

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
};
