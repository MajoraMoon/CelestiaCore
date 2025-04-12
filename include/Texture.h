#pragma once

// clang-format off


/**
 * 
 * Simple texture class. It combines the Ressources.h/cpp and creates an usable texture
 * 
 */

#include "Resources.h"

// clang-format on

class Texture {

public:
  Texture(const std::string &path);
  ~Texture();

  void bind(GLuint unit) const;

private:
  GLuint m_id = 0;
};
