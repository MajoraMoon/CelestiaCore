#pragma once

// clang-format off

#include <glad/glad.h>
#include <string>

#include "Resources.h"

// clang-format on

class Texture {

public:
  Texture(const std::string &path);
  ~Texture();

  void bind(GLuint unit) const;

private:
  GLuint id = 0;
  int width = 0;
  int height = 0;
};
