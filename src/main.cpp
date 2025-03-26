// clang-format off

#include <iostream>

#include <SDL3/SDL.h>

#include "FrameTimer.h"
#include "Renderer.h"
#include "WindowSDLGL.h"

// clang-format on

// Vsync stuff
typedef enum { VSyncOFF = 0, VSyncON = 1 } VsyncMode;
static VsyncMode currentVsyncMode = VSyncOFF;

static void activateVsync(VsyncMode mode) {

  if (SDL_GL_SetSwapInterval(static_cast<int>(mode)) == false) {
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

  WindowSDLGL window("LunaCore", "0.1", 1920, 1090);

  if (!window.getSDLGLWindow() || !window.getGLContext()) {
    std::cerr << "Failed to initialize Window or OpenGL context." << std::endl;

    return -1;
  }

  bool running = true;
  SDL_Event event;

  Renderer renderer;
  FrameTimer frameTimer;

  // main loop
  while (running) {
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL3_ProcessEvent(&event);

      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
      // Event when a key is pressed
      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
          running = false;
        }
      }
      // adjust the resolution to provide openGL correct data
      if (event.window.type == SDL_EVENT_WINDOW_RESIZED) {

        window.setSDLGLWindowSize(event.window.data1, event.window.data2);
      }
    }

    renderer.renderFrame(window.getSDLGLWindowWidth(),
                         window.getSDLGLWindowHeight());
    frameTimer.update();

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
