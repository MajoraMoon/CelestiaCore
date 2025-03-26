#ifndef RENDERER_H
#define RENDERER_H
// clang-format off

#include <cstdio>
#include <cstdlib>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "Shader.h"
#include "Resources.h"

// clang-format on

class Renderer {

public:
  Renderer();
  ~Renderer();
  void renderFrame(unsigned int width, unsigned int height);

private:
  GLuint vao, vbo, ebo;
  Shader shader;
  GLuint texture1;
  GLuint texture2;
};

#endif
