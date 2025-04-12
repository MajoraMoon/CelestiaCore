// clang-format off
#include "pch.h"
#include "CelestiaCore.h"
// clang-format on

CelestiaCore::CelestiaCore()
    : window("CelestiaCore", "0.3", eventBus), stateManager(eventBus, appState),
      frameTimer(eventBus), scene(eventBus), guiManager(window, eventBus),
      inputManger(eventBus), renderer(eventBus, scene) {}

void CelestiaCore::run() {

  eventBus.subscribe<QuitEvent>([this](const Event &e) { quitCelestiaCore(); });

  // main loop
  while (running) {

    frameTimer.update();

    while (SDL_PollEvent(&event)) {

      inputManger.processEvent(event);

      guiManager.processGUIEvent(&event);
    }

    scene.update();

    renderer.renderFrame();

    // dear ImGui-rendering
    guiManager.newFrame();
    guiManager.render();

    SDL_GL_SwapWindow(window.getSDLGLWindow());
  }
}
