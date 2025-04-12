#pragma once

// clang-format off

#include "EventBus.h"
#include "Events.h"

#include "WindowSDLGL.h"

// clang-format on

/**
 *
 * A simple GuiManaging class which uses the dear imgui library.
 *
 */

class GuiManager {

public:
  GuiManager(WindowSDLGL &window, EventBus &eventBus);
  ~GuiManager();

  void processGUIEvent(const SDL_Event *event);
  void newFrame();
  void render();
  void toggleVsync(bool vsyncEnabled);

private:
  EventBus &eventBus;
  WindowSDLGL &window;

  // actual imgui windows to render
  void showStatsWindow();
  void showShortcutsWindow();

  // inner enum class, so it does not conflict with global on/off values
  // somewhere else. idk how c++ works honestly, I know object oriented design
  // but c++ is something else lol
  enum class VsyncMode { Off = 0, On = 1 };
  VsyncMode m_CurrentVsyncMode = VsyncMode::Off;

  unsigned int width = 1920;
  unsigned int height = 1080;

  bool guiVisible = true;
  bool mouseVisible = false;
  bool simulationPaused = false;

  float deltaTime = 0.0f;
  float currentTime = 0.0f;
  float simulationTime = 0.0f;
  float stableFPS = 0.0f;
};
