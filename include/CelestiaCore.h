#pragma once

// clang-format off
#include "EventBus.h"
#include "Events.h"
#include "WindowSDLGL.h"
#include "Renderer.h"
#include "FrameTimer.h"
#include "Scene.h"
#include "InputManager.h"
#include "GuiManager.h"
#include "AppState.h"

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

  EventBus eventBus;
  AppState appState;
  StateManager stateManager;

public:
  CelestiaCore();

  void run();

private:
  bool running = true;

  void quitCelestiaCore() { running = !running; }

  WindowSDLGL window;
  FrameTimer frameTimer;
  InputManager inputManger;
  Scene scene;
  Renderer renderer;
  GuiManager guiManager;
};