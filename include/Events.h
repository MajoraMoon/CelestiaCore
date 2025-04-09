#pragma once
// clang-format off
#include "pch.h"
#include "EventBus.h"
// clang-format on

// Keyboard events
struct KeyEvent : Event {
  SDL_Scancode scancode;
  bool pressed;
};

// Mouse movement events
struct MouseMoveEvent : Event {
  float xrel;
  float yrel;
};

// Mouse scroll events
struct MouseScrollEvent : Event {
  float yoffset;
};

// Window resize events
struct WindowResizeEvent : Event {
  int width;
  int height;
};

// Add these to CommonEvents.h
struct ToggleGuiEvent : Event {};
struct ToggleMouseEvent : Event {};
struct PauseEvent : Event {};
struct MaximizeWindowEvent : Event {};
struct QuitEvent : Event {};