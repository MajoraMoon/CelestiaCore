// clang-format off
#include "pch.h"
#include "Scene.h"
// clang-format on

Scene::Scene(FrameTimer &frameTimer)
    : frameTimer(frameTimer), camera(glm::vec3(0.0f, 0.0f, 3.0f)) {

  // clang-format off

  cubePositions = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
  };

  // clang-format on
}

void Scene::update() {
  cubeTransforms.clear();

  for (size_t i = 0; i < cubePositions.size(); ++i) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i;

    // Add time-based rotation for cubes where i % 3 == 0
    if (i % 3 == 0) {
      angle +=
          frameTimer.getCurrentTime() * 25.0f; // Keep the rotation over time
    }

    model =
        glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    cubeTransforms.push_back(model);
  }
}