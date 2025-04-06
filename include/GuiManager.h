#pragma once

// clang-format off

#include <SDL3/SDL.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

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

  void toggleVisibility() { m_Visible = !m_Visible; }
  bool IsVisible() const { return m_Visible; }

private:
  void showInformationWindow();

  WindowSDLGL &m_Window;
  FrameTimer &m_FrameTimer;
  // inner enum class, so it does not conflict with global on/off values
  // somewhere else. idk how c++ works honestly, I know object oriented design
  // but c++ is something else lol
  enum class VsyncMode { Off = 0, On = 1 };
  VsyncMode m_CurrentVsyncMode = VsyncMode::Off;
  bool m_Visible = true;
};
