#include <Renderer.h>

Renderer::Renderer()
    : shader("../shader/vertexShader.vert", "../shader/fragmentShader.frag") {
  // Turn off VSync
  SDL_GL_SetSwapInterval(0);

  // Vertex-Data: position, color, coordinates
  GLfloat vertexData[] = {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                          0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,
                          -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f,
                          0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f};
  GLuint elementBufferData[] = {0, 1, 2, 1, 3, 2};

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementBufferData),
               elementBufferData, GL_STATIC_DRAW);

  // Attribute-Pointer
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                        (GLvoid *)0);

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                        (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                        (GLvoid *)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  // load Texture 1
  int widthImg, heightImg;
  unsigned char *imgData = loadImage(
      "../assets/textures/rocky_terrain_diff_4k.jpg", &widthImg, &heightImg);

  if (!imgData) {
    fprintf(stderr, "Failed to load texture 1");
    return;
  }

  glGenTextures(1, &texture1);

  glBindTexture(GL_TEXTURE_2D, texture1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB,
               GL_UNSIGNED_BYTE, imgData);
  glGenerateMipmap(GL_TEXTURE_2D);
  free(imgData);

  // load Texture 2
  imgData = loadImage("../assets/textures/awesomeface.png", &widthImg,
                      &heightImg, false, true);

  if (!imgData) {
    fprintf(stderr, "Failed to load texture 2");
    return;
  }

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // note: it is a png container with transparency ability, so its GL_RGBA not
  // GL_RGB
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, imgData);

  glGenerateMipmap(GL_TEXTURE_2D);
  free(imgData);

  shader.use();
  glUniform1i(glGetUniformLocation(shader.getID(), "texture1"),
              0); // Texture-Unit 0
  glUniform1i(glGetUniformLocation(shader.getID(), "texture2"),
              1); // Texture-Unit 1
}

void Renderer::renderFrame(unsigned int width, unsigned int height) {
  glViewport(0, 0, width, height);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);

  shader.use();
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Renderer::~Renderer() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteTextures(1, &texture1);
  glDeleteTextures(1, &texture2);
}