#pragma once
// clang-format off

#include "pch.h"

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

// triggers for appStates (used for global states not controlled by the gui)
struct ToggleMouseVisibilityEvent : Event {};
struct ToggleGuiEvent : Event {};
struct PauseEvent : Event {};
struct MaximizeWindowEvent : Event {};
struct QuitEvent : Event {};

// AppState event changes
struct MouseVisibilityChanged : Event {
  bool mouseVisible;
  MouseVisibilityChanged(bool v) : mouseVisible(v) {}
};

struct GuiVisibilityChanged : Event {
  bool guiVisible;
  GuiVisibilityChanged(bool v) : guiVisible(v) {}
};

struct SimulationPausedChanged : Event {
  bool simulationPaused;
  SimulationPausedChanged(bool p) : simulationPaused(p) {}
};

struct WindowMaximizedChanged : Event {
  bool windowMaximized;
  WindowMaximizedChanged(bool m) : windowMaximized(m) {}
};

// GUI controlled
struct MouseSensitivityChanged : Event {
  float sensitivity;
  MouseSensitivityChanged(float s) : sensitivity(s) {}
};