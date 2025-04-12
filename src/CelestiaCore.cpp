// clang-format off
#include "pch.h"
#include "CelestiaCore.h"
// clang-format on

CelestiaCore::CelestiaCore()
    : window("CelestiaCore", "0.3", eventBus), stateManager(eventBus, appState),
      frameTimer(eventBus), scene(eventBus), guiManager(window, eventBus),
      inputManger(eventBus), renderer(window, eventBus, scene) {

  // set up right resolution after all classes are created and the eventBus is
  // working
  window.publishCurrentWindowSize();
}

void CelestiaCore::run() {

  eventBus.subscribe<QuitEvent>([this](const Event &e) { quitCelestiaCore(); });

  // main loop
  while (m_running) {

    frameTimer.update();

    while (SDL_PollEvent(&event)) {

      inputManger.processEvent(event);

      guiManager.processGUIEvent(&event);
    }

    scene.update();

    renderer.renderFrame();

    guiManager.render();

    SDL_GL_SwapWindow(window.getSDLGLWindow());
  }
}
