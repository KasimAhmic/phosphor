cmake_minimum_required(VERSION 3.31)
project(phosphor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# spdlog configuration
set(SPDLOG_BUILD_EXAMPLE        OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_EXAMPLE_HO     OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS          OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_TESTS_HO       OFF CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_BENCH          OFF CACHE BOOL "" FORCE)
set(SPDLOG_INSTALL              OFF CACHE BOOL "" FORCE)

# SDL configuration
set(SDL_STATIC                  ON  CACHE BOOL "" FORCE)
set(SDL_SHARED                  OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS           OFF CACHE BOOL "" FORCE)

# SDL_ttf configuration
set(SDLTTF_VENDORED             ON  CACHE BOOL "" FORCE)
set(SDLTTF_HARFBUZZ             OFF CACHE BOOL "" FORCE)
set(SDLTTF_PLUTOSVG             OFF CACHE BOOL "" FORCE)

# SDL_image configuration
set(SDLIMAGE_VENDORED           ON  CACHE BOOL "" FORCE)
set(SDLIMAGE_BACKEND_STB        ON  CACHE BOOL "" FORCE)
set(SDLIMAGE_PNG                ON  CACHE BOOL "" FORCE)
set(SDLIMAGE_PNG_LIBPNG         OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_AVIF               OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_ANI                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_BMP                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_GIF                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JPG                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JPX                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TIF                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP               OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_LBM                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PCX                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PNM                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_QOI                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_SVG                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TGA                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XCF                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XPM                OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XV                 OFF CACHE BOOL "" FORCE)

# SDL_mixer configuration
set(SDLMIXER_VENDORED           ON  CACHE BOOL "" FORCE)
set(SDLMIXER_WAVE               ON  CACHE BOOL "" FORCE)
set(SDLMIXER_AIFF               OFF CACHE BOOL "" FORCE)
set(SDLMIXER_VOC                OFF CACHE BOOL "" FORCE)
set(SDLMIXER_AU                 OFF CACHE BOOL "" FORCE)
set(SDLMIXER_FLAC               OFF CACHE BOOL "" FORCE)
set(SDLMIXER_GME                OFF CACHE BOOL "" FORCE)
set(SDLMIXER_MOD                OFF CACHE BOOL "" FORCE)
set(SDLMIXER_MP3                OFF CACHE BOOL "" FORCE)
set(SDLMIXER_MIDI               OFF CACHE BOOL "" FORCE)
set(SDLMIXER_OPUS               OFF CACHE BOOL "" FORCE)
set(SDLMIXER_VORBIS_STB         OFF CACHE BOOL "" FORCE)
set(SDLMIXER_VORBIS_VORBISFILE  OFF CACHE BOOL "" FORCE)
set(SDLMIXER_VORBIS_TREMOR      OFF CACHE BOOL "" FORCE)
set(SDLMIXER_WAVPACK            OFF CACHE BOOL "" FORCE)

add_subdirectory(external/SDL       EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_mixer EXCLUDE_FROM_ALL)
add_subdirectory(external/SDL_ttf   EXCLUDE_FROM_ALL)
add_subdirectory(external/spdlog    EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/application.cpp
  src/instruction.hpp
  src/cpu.hpp
  src/cpu.cpp
  src/addressing_mode.hpp
  src/opcode.hpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    spdlog::spdlog
)

include(CTest)

if (BUILD_TESTING)
  add_subdirectory(external/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest EXCLUDE_FROM_ALL)

  add_executable(${PROJECT_NAME}_tests
      tests/test_main.cpp
  )

  target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE
      GTest::gtest
      spdlog::spdlog
  )

  include(GoogleTest)
  gtest_discover_tests(${PROJECT_NAME}_tests)
endif ()
