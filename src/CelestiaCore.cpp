// clang-format off
#include "pch.h"
#include "CelestiaCore.h"
#include "EventSystem.h"
// clang-format on

namespace Celestia {

CelestiaCore::CelestiaCore()
    : window("CelestiaCore", "0.4", eventBus, appState),
      frameTimer(eventBus, appState), inputManager(eventBus, appState),
      renderer(window, eventBus, scene, appState), scene(eventBus, frameTimer),
      guiManager(window, eventBus, appState) {

  setupStateChangesSubscriptions();
}

void CelestiaCore::run() {

  // main loop
  while (!appState.celestiaCore.quit) {

    frameTimer.update();

    while (SDL_PollEvent(&event)) {
      inputManager.processEvent(event);

      guiManager.processGUIEvent(&event);
    }

    scene.update();

    renderer.renderFrame();

    guiManager.render();

    SDL_GL_SwapWindow(window.getSDLGLWindow());
  }
}

void CelestiaCore::setupStateChangesSubscriptions() {

  eventBus.on<QuitEvent>(
      [this](const auto &ev) { appState.celestiaCore.quit = true; });

  eventBus.on<SetMouseVisibilityEvent>(
      [this](const auto &ev) { appState.window.mouseVisibility = ev.visible; });

  eventBus.on<SetGuiVisibilityEvent>(
      [this](const auto &ev) { appState.gui.visibility = ev.visible; });

  eventBus.on<SetPauseEvent>(
      [this](const auto &ev) { appState.simulation.paused = ev.paused; });

  eventBus.on<SetWindowMaximizedEvent>(
      [this](const auto &ev) { appState.window.maximized = ev.maximized; });

  eventBus.on<SetFullscreenModeEvent>(
      [this](const auto &ev) { appState.window.fullscreen = ev.fullscreen; });

  eventBus.on<SetVsyncModeEvent>(
      [this](const auto &ev) { appState.window.vsync = ev.vsync; });

  eventBus.on<SetMouseSensitivityEvent>([this](const auto &ev) {
    appState.camera.mouseSensitivity = ev.sensitivity;
  });
}

} // namespace Celestia
