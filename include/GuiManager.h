#pragma once

// clang-format off

#include "WindowSDLGL.h"
#include "FrameTimer.h"

// clang-format on

/**
 *
 * A simple GuiManaging class which uses the dear imgui library.
 *
 */

class GuiManager {

public:
  GuiManager(WindowSDLGL &window, FrameTimer &frameTimer);
  ~GuiManager();

  void processGUIEvent(const SDL_Event *event);
  void newFrame();
  void render();
  void toggleVsync(bool vsyncEnabled);

  void toggleVisibility() { visible = !visible; }
  bool IsVisible() const { return visible; }

private:
  // actual imgui windows to render
  void showStatsWindow();
  void showShortcutsWindow();

  WindowSDLGL &window;
  FrameTimer &frameTimer;
  // inner enum class, so it does not conflict with global on/off values
  // somewhere else. idk how c++ works honestly, I know object oriented design
  // but c++ is something else lol
  enum class VsyncMode { Off = 0, On = 1 };
  VsyncMode m_CurrentVsyncMode = VsyncMode::Off;
  bool visible = true;
};
