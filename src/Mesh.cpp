// clang-format off
#include "pch.h"
#include "Mesh.h"
#include "EventSystem.h"
// clang-format on

// I will rewrite this class later. its not the best atm

namespace Celestia {

Mesh::Mesh(const std::vector<float> &vertexData) {
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float),
               vertexData.data(), GL_STATIC_DRAW);

  GLenum err = glGetError();
  if (err != GL_NO_ERROR) {
    std::cerr << "OpenGL error in Mesh constructor: " << err << "\n";
  }

  // Attribute-Pointer
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid *)0);

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
                        (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  // the glEnableVertexAttribArray(x) points to the shader location
  // "layout(location = x) in vec3 aPos;

  vertexCount = vertexData.size() / 5; // 3 pos + 2 tex
}

Mesh::~Mesh() {

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

void Mesh::draw() const {
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

} // namespace Celestia
