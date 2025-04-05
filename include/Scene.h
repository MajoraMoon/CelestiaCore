#pragma once

// clang-format off

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

// clang-format on 

class Scene {

public:
  Scene();
  // logic update for rendered objects (e.g. physics)
  void update(float deltaTime);

  std::vector<glm::mat4> cubeTransforms;  


// Camera is part of the scene
  Camera camera;

  private:
  std::vector<glm::vec3> cubePositions;
  float currentTime = 0.0f;

  
};
