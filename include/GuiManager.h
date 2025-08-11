#pragma once

/**
 *
 * A simple GuiManaging class which uses the dear imgui library.
 *
 */

namespace Celestia {

// forward declarations
class WindowSDLGL;
class EventBus;
struct AppState;

class GuiManager {

public:
  GuiManager(WindowSDLGL &window, EventBus &eventBus, AppState &appState);
  ~GuiManager();

  void processGUIEvent(const SDL_Event *event);
  void render();

private:
  WindowSDLGL &window;
  EventBus &eventBus;
  AppState &appState;

  // actual imgui windows to render
  void showStatsWindow();
  void showShortcutsWindow();

  void setupEventSubscriptions();

  unsigned int m_width;
  unsigned int m_height;

  float m_mouseSensitivity;

  float m_deltaTime;
  float m_currentTime;
  float m_simulationTime;
  float m_stableFPS;
};

} // namespace Celestia
