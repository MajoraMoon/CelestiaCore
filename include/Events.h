#pragma once
// clang-format off
#include "pch.h"
#include "EventBus.h"
// clang-format on

// Keyboard events
struct KeyEvent : Event {
  SDL_Scancode scancode;
  bool pressed;

  KeyEvent(SDL_Scancode code, bool isPressed)
      : scancode(code), pressed(isPressed) {}
};

// Mouse movement events
struct MouseMoveEvent : Event {
  float xrel;
  float yrel;

  MouseMoveEvent(float x, float y) : xrel(x), yrel(y) {}
};

// Mouse scroll events
struct MouseScrollEvent : Event {
  float yoffset;

  explicit MouseScrollEvent(float y) : yoffset(y) {}
};

// Window resize events
struct WindowResizeEvent : Event {
  int width;
  int height;

  WindowResizeEvent(int w, int h) : width(w), height(h) {}
};

struct FrameUpdateEvent : Event {

  float deltaTime;
  float lastTime;
  float simulationTime;
  float simulationDeltaTime;
  float stableFPS;
  bool paused;

  FrameUpdateEvent(float deltaTime, float lastTime, float simulationTime,
                   float simulationDeltaTime, float stableFPS, bool paused)
      : deltaTime(deltaTime), lastTime(lastTime),
        simulationTime(simulationTime),
        simulationDeltaTime(simulationDeltaTime), stableFPS(stableFPS),
        paused(paused) {}
};

// triggers for appStates
struct ToggleMouseVisibilityEvent : Event {};
struct ToggleGuiEvent : Event {};
struct PauseEvent : Event {};
struct MaximizeWindowEvent : Event {};

struct QuitEvent : Event {};

// AppState event changes
struct MouseVisibilityChanged : Event {
  bool visible;
  MouseVisibilityChanged(bool v) : visible(v) {}
};

struct GuiVisibilityChanged : Event {
  bool visible;
  GuiVisibilityChanged(bool v) : visible(v) {}
};

struct SimulationPaused : Event {
  bool paused;
  SimulationPaused(bool p) : paused(p) {}
};

struct WindowMaximized : Event {
  bool maximized;
  WindowMaximized(bool m) : maximized(m) {}
};