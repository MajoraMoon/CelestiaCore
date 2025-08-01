// clang-format off
#include "pch.h"
#include "Scene.h"
#include "FrameTimer.h"
// clang-format on

namespace Celestia {

// The Camera is a part of the scene
Scene::Scene(EventBus &eventBus, FrameTimer &frameTimer)
    : eventBus(eventBus), frameTimer(frameTimer) {

  cubePositions = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};
}

void Scene::update() {

  // getting values directly from frameTimer not the eventBus, ensuring values
  // are correct with direct access.
  m_simulationDeltaTime = frameTimer.getSimulationDeltaTime();
  m_simulationTime = frameTimer.getSimulationTime();

  cubeTransforms.clear();

  for (size_t i = 0; i < cubePositions.size(); ++i) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i;

    // Add time-based rotation for cubes where i % 3 == 0
    if (i % 3 == 0) {
      angle += m_simulationTime * 25.0f; // Keep the rotation over time
    }

    model =
        glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    cubeTransforms.push_back(model);
  }
}

} // namespace Celestia
