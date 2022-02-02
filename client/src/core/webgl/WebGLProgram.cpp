#include "WebGLProgram.h"

#include <array>

#include "../../vendor/glm.h"

namespace app {

WebGLProgram::WebGLProgram(const WebGLShader &vertexShader,
                           const WebGLShader &fragmentShader)
    : handle_{glCreateProgram()} {
  glAttachShader(handle_, vertexShader.handle());
  glAttachShader(handle_, fragmentShader.handle());
  glLinkProgram(handle_);
  glUseProgram(handle_);

  GLint is_compiled = GL_FALSE;
  glGetProgramiv(handle_, GL_LINK_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    std::array<GLchar, kMaxLogLength> log{};
    glGetProgramInfoLog(handle_, sizeof(log), nullptr, log.data());
    std::cout << "ERROR::program::COMPILATION_FAILED\n"
              << log.data() << std::endl;
    glDeleteProgram(handle_);
    handle_ = 0;
    return;
  }

  std::cout << "created WebGLProgram " << handle_ << std::endl;
  debug();
}

WebGLProgram::~WebGLProgram() {
  if (handle_ > 0) {
    std::cout << "~WebGLProgram " << handle_ << std::endl;
    glDeleteProgram(handle_);
    handle_ = 0;
  }
}

void WebGLProgram::debug() {
  GLuint i;
  GLint count;

  GLint size;   // size of the variable
  GLenum type;  // type of the variable (float, vec3 or mat4, etc)

  const GLsizei buf_size = 32;  // maximum name length
  GLchar name[buf_size];        // variable name in GLSL
  GLsizei length;               // name length

  glGetProgramiv(handle_, GL_ACTIVE_ATTRIBUTES, &count);
  printf("Active Attributes: %d\n", count);
  for (i = 0; i < count; i++) {
    attributes_.emplace_back(name);
    glGetActiveAttrib(handle_, i, buf_size, &length, &size, &type, name);
    GLint loc = glGetAttribLocation(handle_, name);
    printf("Attribute #%d Type: %u Name: %s Loc: %d\n", i, type, name, loc);
  }

  glGetProgramiv(handle_, GL_ACTIVE_UNIFORMS, &count);
  printf("Active Uniforms: %d\n", count);

  for (i = 0; i < count; i++) {
    glGetActiveUniform(handle_, i, buf_size, &length, &size, &type, name);
    auto loc = get_uniform_location(name);
    uniforms_.emplace_back(name);
    printf("Uniform #%d Type: %u Loc: %u Name: %s\n", i, type, loc, name);
  }
}

auto WebGLProgram::use() const noexcept -> bool {
  if (handle_ > 0) {
    glUseProgram(handle_);
  } else {
    std::cerr << "WebGLProgram can't use" << handle_ << std::endl;
  }
  return handle_ != 0U;
}

auto WebGLProgram::get_uniform_location(const char *name) const -> int {
  auto loc = glGetUniformLocation(handle_, name);
  if (loc < 0) {
    std::cerr << "Uniform not found for " << name << std::endl;
  }

  return loc;
}

void WebGLProgram::set_uniform(int loc, const mat4 &value) {
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void WebGLProgram::set_uniform(int loc, const vec4 &value) {
  glUniform4f(loc, value[0], value[1], value[2], value[3]);
}

void WebGLProgram::set_uniform(int loc, const int value) {
  glUniform1i(loc, value);
}

}  // namespace app