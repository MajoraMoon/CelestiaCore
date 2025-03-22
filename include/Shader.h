#ifndef SHADER_H
#define SHADER_H

// clang-format off

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

// clang-format on

class Shader {

public:
  Shader(const std::string &vertexPath, const std::string &fragmentPath);
  ~Shader();

  void use() const;
  GLuint getID() const { return ID; }

private:
  GLuint ID;
  std::string readFile(const std::string &filePath);
  void checkCompileErrors(GLuint shader, const std::string &type);
};

#endif