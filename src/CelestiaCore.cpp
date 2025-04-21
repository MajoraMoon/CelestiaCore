// clang-format off
#include "pch.h"
#include "CelestiaCore.h"
#include "EventSystem.h"

// clang-format on

namespace Celestia
{

CelestiaCore::CelestiaCore()
    : stateManager(eventBus, appState), window("CelestiaCore", "0.4", eventBus), frameTimer(eventBus),
      inputManger(eventBus, appState), renderer(window, eventBus, scene), scene(eventBus, frameTimer),
      guiManager(window, eventBus, appState)
{

    // set up right resolution after all classes are created and the eventBus is
    // working
    stateManager.publishInitialStates();
    window.publishCurrentWindowSize();

    eventBus.subscribe<CelestiaCoreQuitChanged>([this](const CelestiaCoreQuitChanged &ev) { m_quit = ev.quit; });
}

void CelestiaCore::run()
{

    // main loop
    while (!m_quit)
    {

        frameTimer.update();

        while (SDL_PollEvent(&event))
        {
            inputManger.processEvent(event);

            guiManager.processGUIEvent(&event);
        }

        scene.update();

        renderer.renderFrame();

        guiManager.render();

        SDL_GL_SwapWindow(window.getSDLGLWindow());
    }
}

} // namespace Celestia
