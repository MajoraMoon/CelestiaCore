#pragma once

// clang-format off

#include "WindowSDLGL.h"
#include "Renderer.h"
#include "FrameTimer.h"
#include "Scene.h"
#include "InputManager.h"
#include "GuiManager.h"

// clang-format on

class CelestiaCore {

public:
  CelestiaCore();
  void run();

private:
  WindowSDLGL window;
  FrameTimer frameTimer;
  InputManager inputManger;
  Scene scene;
  Renderer renderer;
  GuiManager guiManager;

  void handleWindowResize(int width, int height);
};