#pragma once

// clang-format off

#include "Camera.h"
#include "FrameTimer.h"

#include "EventBus.h"
#include "Events.h"

// clang-format on 

class Scene {

public:
  Scene(EventBus& eventBus);
  
  // logic update for rendered objects (e.g. physics)
  void update();

  std::vector<glm::mat4> cubeTransforms;  




  private:
  EventBus& eventBus;
  std::vector<glm::vec3> cubePositions;

  float m_simulationDeltaTime = 0.0f;
  float m_simulationTime = 0.0f;

  
};
