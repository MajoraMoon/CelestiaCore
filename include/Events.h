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

// Add these to CommonEvents.h
struct ToggleGuiEvent : Event {};
struct ToggleMouseEvent : Event {};
struct PauseEvent : Event {};
struct MaximizeWindowEvent : Event {};
struct QuitEvent : Event {};