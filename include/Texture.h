#pragma once

/**
 *
 * Simple texture class. It combines the Ressources.h/cpp and creates an usable
 * texture
 *
 */

#include "Resources.h"

namespace Celestia {

class Texture {

public:
  Texture(const std::string &path);
  ~Texture();

  void bind(GLuint unit) const;

private:
  GLuint m_id = 0;
};

} // namespace Celestia
