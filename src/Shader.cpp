#include <Shader.h>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {

  std::string vertexCode = readFile(vertexPath);
  std::string fragmentCode = readFile(fragmentPath);

  if (vertexCode.empty() || fragmentCode.empty()) {
    std::cerr << "ERROR: Shader source code could not be read" << std::endl;
    ID = 0;
    return;
  }

  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();

  // compile vertex Shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
  glCompileShader(vertexShader);
  checkCompileErrors(vertexShader, "VERTEX");

  // compile fragment Shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
  glCompileShader(fragmentShader);
  checkCompileErrors(fragmentShader, "FRAGMENT");

  // create Shader-programm and linking
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);
  checkCompileErrors(ID, "PROGRAM");

  // shader exists now, the raw data can be deleted
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

std::string Shader::readFile(const std::string &filePath) {

  std::ifstream file(filePath);
  if (!file) {
    std::cerr << "ERROR: Unable to open file " << filePath << std::endl;
    return "";
  }
  std::stringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

void Shader::checkCompileErrors(GLuint shader, const std::string &type) {
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
      std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
      std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                << infoLog << std::endl;
    }
  }
}

void Shader::use() const { glUseProgram(ID); }

Shader::~Shader() { glDeleteProgram(ID); }