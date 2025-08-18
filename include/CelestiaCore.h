#pragma once

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

#include "EventSystem.h"
#include "FrameTimer.h"
#include "GuiManager.h"
#include "Renderer.h"
#include "Scene.h"
#include "WindowSDLGL.h"

namespace Celestia {

class CelestiaCore {

  // The EventBus and ESPECIALLY the AppState should be created before any other
  // class. Because the AppState is holding the initiale States for many events.
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
  InputManager inputManager;
  Renderer renderer;
  Scene scene;
  GuiManager guiManager;

  bool m_quit = false;
};

} // namespace Celestia
