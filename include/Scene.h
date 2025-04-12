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


// Camera is part of the scene. Renderer needs information through the scene's camera
// There will be only one camera anyway
  Camera camera;

  private:
  EventBus& eventBus;
  std::vector<glm::vec3> cubePositions;

  float simulationDeltaTime = 0.0f;
  float simulationTime = 0.0f;

  
};
