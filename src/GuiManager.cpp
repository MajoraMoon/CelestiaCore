// clang-format off
#include "pch.h"
#include "GuiManager.h"
// clang-format on

GuiManager::GuiManager(WindowSDLGL &window, EventBus &eventBus)
    : window(window), eventBus(eventBus) {

  float scaleFactor = SDL_GetWindowDisplayScale(window.getSDLGLWindow());

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.FontGlobalScale = scaleFactor;
  ImGui::GetStyle().ScaleAllSizes(scaleFactor);

  ImGui::StyleColorsDark();

  ImGui_ImplSDL3_InitForOpenGL(window.getSDLGLWindow(), window.getGLContext());
  ImGui_ImplOpenGL3_Init("#version 460");

  // GUI events
  eventBus.subscribe<GuiVisibilityChanged>([this](const Event &e) {
    const auto &ev = static_cast<const GuiVisibilityChanged &>(e);
    guiVisible = ev.visible;
  });

  eventBus.subscribe<FrameUpdateEvent>([this](const Event &e) {
    const auto &ev = static_cast<const FrameUpdateEvent &>(e);

    currentTime = ev.lastTime;
    simulationTime = ev.simulationTime;
    deltaTime = ev.deltaTime;
    stableFPS = ev.stableFPS;
  });

  eventBus.subscribe<MouseVisibilityChanged>([this](const Event &e) {
    const auto &ev = static_cast<const MouseVisibilityChanged &>(e);
    mouseVisible = ev.visible;
  });

  eventBus.subscribe<WindowResizeEvent>([this](const Event &e) {
    const auto &ev = static_cast<const WindowResizeEvent &>(e);
    width = ev.width;
    height = ev.height;
  });
}

GuiManager::~GuiManager() {

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

void GuiManager::processGUIEvent(const SDL_Event *event) {

  if (mouseVisible) {
    ImGui_ImplSDL3_ProcessEvent(event);
  }
}

void GuiManager::newFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}

void GuiManager::render() {

  // dear ImGui needs to end the rendering even if nothing is displayed. So only
  // if Visibility is toggled on, the private functions from imgui are shown
  if (guiVisible) {
    showShortcutsWindow();
    showStatsWindow();
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::toggleVsync(bool vsyncEnabled) {
  m_CurrentVsyncMode = vsyncEnabled ? VsyncMode::On : VsyncMode::Off;
  SDL_GL_SetSwapInterval(static_cast<int>(m_CurrentVsyncMode));
}

// FUNCTION CREATION FOR IMGUI WINDOWS

// actual window to render. This can be extended with other functions later if
// needed. Just using Imgui::Begin and end
void GuiManager::showStatsWindow() {
  ImGui::Begin("Extra Information");

  // I think packing this code to visual the time better into another function
  // is more verbose than just letting it in here.

  int totalSeconds = static_cast<int>(currentTime);
  int milliseconds = static_cast<int>((currentTime - totalSeconds) * 1000);

  int hours = totalSeconds / 3600;
  int minutes = (totalSeconds % 3600) / 60;
  int seconds = totalSeconds % 60;

  ImGui::Text("Runtime: %02d:%02d:%02d.%03d", hours, minutes, seconds,
              milliseconds);
  ImGui::Text("Simulation Runtime (seconds): %.2f", simulationTime);
  ImGui::Text("Delta time: %.3f", deltaTime);
  ImGui::Text("FPS (average): %.3f", stableFPS);
  ImGui::Spacing();
  ImGui::Text("Resolution: %ix%i", width, height);

  // VSync Combo Box
  const char *vsyncOptions[] = {"VSync Off", "VSync On"};
  int currentVsyncIndex = static_cast<int>(m_CurrentVsyncMode);

  if (ImGui::Combo("VSync Mode", &currentVsyncIndex, vsyncOptions, 2)) {
    toggleVsync(currentVsyncIndex == 1);
  }

  ImGui::End();
}

void GuiManager::showShortcutsWindow() {
  ImGui::Begin("Hotkeys");
  ImGui::Text("Press 'M' to show/hide the mouse cursor.");
  ImGui::Text("Press 'F' to maximize the window.");
  ImGui::Text("Press 'F1' to hide the gui window.");
  ImGui::Text("Press 'P' to pause the simulation");
  ImGui::End();
}