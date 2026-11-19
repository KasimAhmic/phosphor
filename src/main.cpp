#define SDL_MAIN_USE_CALLBACKS

#include <cstdint>
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <spdlog/spdlog.h>

#include "application.hpp"

struct AppState {
  std::unique_ptr<Application> app;
  uint64_t last_update_time;
};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
  *appstate = nullptr;

  SDL_SetAppMetadata("com.user.application", "Application", "1.0.0");

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    spdlog::error("SDL_Init failed: {}", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!TTF_Init()) {
    spdlog::error("TTF_Init failed: {}", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  if (!MIX_Init()) {
    spdlog::error("MIX_Init failed: {}", SDL_GetError());
    TTF_Quit();
    return SDL_APP_FAILURE;
  }

  try {
    std::unique_ptr<Application> app = std::make_unique<Application>();

    app->init();

    *appstate = new AppState{
        .app              = std::move(app),
        .last_update_time = SDL_GetPerformanceCounter(),
    };
  } catch (const std::exception& e) {
    spdlog::error("Failed to initialize Application: {}", e.what());

    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
  AppState* context = static_cast<AppState*>(appstate);

  const uint64_t now        = SDL_GetPerformanceCounter();
  const double delta_time   = static_cast<double>(now - context->last_update_time) /
                              static_cast<double>(SDL_GetPerformanceFrequency());
  context->last_update_time = now;

  context->app->update(delta_time);
  context->app->render();

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
  return static_cast<AppState*>(appstate)->app->handle_event(*event);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
  delete static_cast<AppState*>(appstate);

  MIX_Quit();
  TTF_Quit();
}
