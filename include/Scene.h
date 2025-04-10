#pragma once

// clang-format off

#include "Camera.h"
#include "FrameTimer.h"

#include "EventBus.h"
#include "Events.h"

// clang-format on 

class Scene {

public:
  Scene(FrameTimer& frameTimer, EventBus& eventBus);
  
  // logic update for rendered objects (e.g. physics)
  void update();

  std::vector<glm::mat4> cubeTransforms;  


// Camera is part of the scene
  Camera camera;

  private:
  EventBus& eventBus;
  FrameTimer& frameTimer;
  std::vector<glm::vec3> cubePositions;
  float currentTime = 0.0f;

  
};
