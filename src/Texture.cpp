// clang-format off
#include "pch.h"
#include "Texture.h"
// clang-format on

Texture::Texture(const std::string &path) {

  int widthImg, heightImg;
  unsigned char *imgData = loadImage(path.c_str(), &widthImg, &heightImg);

  if (!imgData) {
    fprintf(stderr, "Failed to load texture");
    return;
  }

  glGenTextures(1, &m_id);
  glBindTexture(GL_TEXTURE_2D, m_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLenum format = GL_RGB;

  // std::string::npos means "not found", it contains the value -1.
  // Use RGB for jpg images and RGBA for png images, supporting opacity
  if (std::string(path).find(".png") != std::string::npos) {
    format = GL_RGBA;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, format, widthImg, heightImg, 0, format,
               GL_UNSIGNED_BYTE, imgData);
  glGenerateMipmap(GL_TEXTURE_2D);
  free(imgData);
}

Texture::~Texture() { glDeleteTextures(1, &m_id); }

void Texture::bind(GLuint unit) const {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, m_id);
}