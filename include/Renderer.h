#pragma once
// clang-format off

#include <cstdio>
#include <cstdlib>
#include <vector>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Resources.h"
#include "Camera.h"
#include "FrameTimer.h"

// clang-format on

class Renderer {

public:
  Renderer(FrameTimer &frameTimer);
  ~Renderer();
  void renderFrame(unsigned int width, unsigned int height);
  Camera &getCamera() { return camera; }

private:
  GLuint vao, vbo, ebo;
  Shader shader;
  Camera camera;
  GLuint texture1;
  GLuint texture2;
  FrameTimer &frameTimer;

  std::vector<glm::vec3> cubePositions;
};
