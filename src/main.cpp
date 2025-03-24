// clang-format off

#include <iostream>

#include <SDL3/SDL.h>

#include "FrameTimer.h"
#include "Renderer.h"
#include "WindowSDLGL.h"

// clang-format on

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// Vsync stuff
typedef enum { VSyncOFF = 0, VSyncON = 1 } VsyncMode;
static VsyncMode currentVsyncMode = VSyncOFF;

static void activateVsync(VsyncMode mode) {

  if (SDL_GL_SetSwapInterval(static_cast<int>(mode)) != 0) {
    SDL_Log("Could not set Swap-Interval (VSync) correctly: %s\n",
            SDL_GetError());
  } else {
    currentVsyncMode = mode;
  }
}

// Dear ImGui window with some information
void ShowInformationWindow(FrameTimer &frameTimer) {
  ImGui::Begin("some Information");
  ImGui::Text("Delta Time: %.5f", frameTimer.getDeltaTime());
  ImGui::Text("FPS (per second): %.1f", frameTimer.getFPS());
  const char *vsyncOptions[] = {"VSync Off", "VSync On"};
  int currentVSyncIndex = static_cast<int>(currentVsyncMode);
  if (ImGui::Combo("VSync Mode", &currentVSyncIndex, vsyncOptions,
                   IM_ARRAYSIZE(vsyncOptions))) {
    currentVsyncMode = static_cast<VsyncMode>(currentVSyncIndex);
    activateVsync(currentVsyncMode);
  }
  ImGui::End();
}

int main(int argc, char *argv[]) {

  WindowSDLGL window("LunaCore", "0.1", SCR_WIDTH, SCR_HEIGHT, true);

  if (!window.getSDLGLWindow() || !window.getGLContext()) {
    std::cerr << "Failed to initialize Window or OpenGL context." << std::endl;

    return -1;
  }

  Renderer renderer;
  FrameTimer frameTimer;

  bool running = true;
  SDL_Event event;

  // main loop
  while (running) {
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);

      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
          running = false;
        }
      }
    }

    frameTimer.update();
    std::cout << "FPS: " << frameTimer.getFPS() << std::endl;
    renderer.renderFrame(SCR_WIDTH, SCR_HEIGHT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ShowInformationWindow(frameTimer);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window.getSDLGLWindow());
  }

  return 0;
}
