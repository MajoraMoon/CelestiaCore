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
  void render();

private:
  EventBus &eventBus;
  WindowSDLGL &window;

  void toggleVsync(bool vsyncEnabled);
  // actual imgui windows to render
  void showStatsWindow();
  void showShortcutsWindow();

  void setupEventSubscriptions();

  // inner enum class, so it does not conflict with global on/off values
  // somewhere else. idk how c++ works honestly, I know object oriented design
  // but c++ is something else lol
  enum class VsyncMode { Off = 0, On = 1 };
  VsyncMode m_CurrentVsyncMode = VsyncMode::Off;

  unsigned int m_width;
  unsigned int m_height;

  bool m_guiVisible = true;
  bool m_mouseVisible = false;
  bool m_simulationPaused = false;

  float m_deltaTime = 0.0f;
  float m_currentTime = 0.0f;
  float m_simulationTime = 0.0f;
  float m_stableFPS = 0.0f;
};
