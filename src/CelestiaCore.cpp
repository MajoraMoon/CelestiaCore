// clang-format off
#include "pch.h"
#include "CelestiaCore.h"
#include "EventSystem.h"

// clang-format on

namespace Celestia {

CelestiaCore::CelestiaCore()
    : stateManager(eventBus, appState), window("CelestiaCore", "0.4", eventBus),
      frameTimer(eventBus), inputManger(eventBus),
      renderer(window, eventBus, scene), scene(eventBus, frameTimer),
      guiManager(window, eventBus, appState) {

  setupEventSubscriptions();

  // set up the initial states of the "global" variables for all classes after
  // their creation set up the right resolution after all classes are created
  stateManager.publishInitialStates();
  window.publishCurrentWindowSize();
}

void CelestiaCore::run() {

  // main loop
  while (!m_quit) {

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

/**
 *
 *  I have this class setupEventSubscriptions in every class working with the
 * Event System. For clarity I will put every subscription into such a function
 * which is called by the constructor fot the class. Even if it only has one
 *  subscription
 *
 */
void CelestiaCore::setupEventSubscriptions() {
  eventBus.subscribe<CelestiaCoreQuitChanged>(
      [this](const auto &ev) { m_quit = ev.quit; });
}

} // namespace Celestia
