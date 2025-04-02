#include "GuiManager.h"

GuiManager::GuiManager(WindowSDLGL &window, FrameTimer &frameTimer)
    : m_Window(window), m_FrameTimer(frameTimer) {

  float scaleFactor = SDL_GetWindowDisplayScale(m_Window.getSDLGLWindow());

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.FontGlobalScale = scaleFactor;
  ImGui::GetStyle().ScaleAllSizes(scaleFactor);

  ImGui::StyleColorsDark();

  ImGui_ImplSDL3_InitForOpenGL(m_Window.getSDLGLWindow(),
                               m_Window.getGLContext());
  ImGui_ImplOpenGL3_Init("#version 460");
}

GuiManager::~GuiManager() {

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

void GuiManager::processGUIEvent(const SDL_Event *event) {
  ImGui_ImplSDL3_ProcessEvent(event);
}

void GuiManager::newFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}

void GuiManager::render() {

  // dear ImGui needs to end the rendering even if nothing is displayed. So only
  // if Visibility is toggled on, the private functions from imgui are shown
  if (m_Visible) {
    showInformationWindow();
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::toggleVsync(bool vsyncEnabled) {
  m_CurrentVsyncMode = vsyncEnabled ? VsyncMode::On : VsyncMode::Off;
  SDL_GL_SetSwapInterval(static_cast<int>(m_CurrentVsyncMode));
}

// actual window to render
void GuiManager::showInformationWindow() {
  ImGui::Begin("Cool Information (Press F1 to hide this window)");
  ImGui::Text("FPS (average): %.3f", m_FrameTimer.getAverageFPS());
  ImGui::Text("Resolution: %ix%i", m_Window.getSDLGLWindowWidth(),
              m_Window.getSDLGLWindowHeight());
  ImGui::Text("Runtime: %.3f", m_FrameTimer.getCurrentTime());

  // VSync Combo Box
  const char *vsyncOptions[] = {"VSync Off", "VSync On"};
  int currentVsyncIndex = static_cast<int>(m_CurrentVsyncMode);

  if (ImGui::Combo("VSync Mode", &currentVsyncIndex, vsyncOptions, 2)) {
    toggleVsync(currentVsyncIndex == 1);
  }

  ImGui::End();
}