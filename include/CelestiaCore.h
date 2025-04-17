#pragma once

// clang-format off

#include "WindowSDLGL.h"
#include "Renderer.h"
#include "FrameTimer.h"
#include "Scene.h"
#include "GuiManager.h"

// clang-format on

/**
 *
 * CelestiaCore is the heart of this program. This Class creates the central
 * classes like:
 *
 * The "WindowSDLGL" class, responsible for the window creation with SDL3.
 *
 * The "FrameTimer" class, responsible for calculating the central time,
 * framerate, deltatime and similar things.
 *
 * The "InputManager" class, responsible for handling Keyboard and mouse
 * events.abort
 *
 * The "Scene" class, this class holds the logic (translation/rotation etc. +
 * physics handling) for Objects.
 *
 * The "Renderer" class, responsible to render the mesh and communicate with the
 * gpu via shaders.
 *
 * The "GuiManager" class, which implements the dear imgui library and can be
 * used to set up stuff on runtime or show information.
 *
 * Moreover, CelestiaCore handles the main loop, every frame all the Meshes and
 * all their Logic are executed in this main loop.
 *
 */

class CelestiaCore {
  SDL_Event event;
  EventBus eventBus;
  AppState appState;
  StateManager stateManager;

public:
  CelestiaCore();

  void run();

private:
  WindowSDLGL window;
  FrameTimer frameTimer;
  InputManager inputManger;
  Renderer renderer;
  Scene scene;
  GuiManager guiManager;

  void quitCelestiaCore() { m_running = !m_running; }

  bool m_running = true;
};