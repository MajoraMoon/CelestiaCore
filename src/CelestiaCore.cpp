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

  eventBus.on<QuitEvent>([this](const auto &) {
    appState.celestiaCore.quit = !appState.celestiaCore.quit;
  });
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

} // namespace Celestia
