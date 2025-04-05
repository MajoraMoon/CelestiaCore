#pragma once

// clang-format off

#include <vector>
#include <glad/glad.h>

// clang-format on

class Mesh {
public:
  Mesh(const std::vector<float> &vertexData);
  ~Mesh();
  void draw() const;

private:
  GLuint vao;
  GLuint vbo;
  size_t vertexCount = 0;
};
