#pragma once

// clang-format off
#include <iostream>
#include <vector>
#include <glad/glad.h>

// clang-format on

/**
 * Temporary class, createst the mesh of objects, will be improved later
 */

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
