#include "GLProgram.h"

#include <array>

#include "../../vendor/glm.h"
#include "../Assets.h"

namespace app {

auto loadShaderIntoString(const std::string &filename) -> std::string {
  std::string contents = Assets::loadString(filename);
#ifdef __EMSCRIPTEN__
  static const std::regex kOpenglVersion{"#version 330 core"};
  contents = std::regex_replace(contents, kOpenglVersion,
                                "#version 300 es\n#define EMSCRIPTEN");
#endif
  return contents;
}

void compile(GLuint handle, const GLShader &vertex, const GLShader &fragment) {
  glAttachShader(handle, vertex.handle());
  glAttachShader(handle, fragment.handle());
  glLinkProgram(handle);
  glUseProgram(handle);

  GLint is_compiled = GL_FALSE;
  glGetProgramiv(handle, GL_LINK_STATUS, &is_compiled);
  if (is_compiled == GL_FALSE) {
    std::array<GLchar, kMaxLogLength> log{};
    glGetProgramInfoLog(handle, sizeof(log), nullptr, log.data());
    std::cout << "ERROR::program::COMPILATION_FAILED\n"
              << log.data() << std::endl;
    return;
  }

  std::cout << "created WebGLProgram " << handle << std::endl;
}

auto GLProgram::create(const std::string &vertex, const std::string &fragment)
    -> GLProgram {
  std::string vertex_shader_source = loadShaderIntoString(vertex);
  std::string fragment_shader_source = loadShaderIntoString(fragment);

  GLShader vertex_shader{WebGLShaderType::kVertex,
                         vertex_shader_source.c_str()};
  GLShader fragment_shader{WebGLShaderType::kFragment,
                           fragment_shader_source.c_str()};
  return GLProgram{vertex_shader, fragment_shader};
}

GLProgram::GLProgram(const GLShader &vertexShader,
                     const GLShader &fragmentShader) {
  compile(handle(), vertexShader, fragmentShader);
  debug();
}

void GLProgram::debug() {
  GLuint i;
  GLint count;

  const GLsizei buf_size = 32;          // maximum name length
  std::array<GLchar, buf_size> name{};  // variable name in GLSL
  GLsizei length;                       // name length
  GLuint type;

  glGetProgramiv(handle(), GL_ACTIVE_ATTRIBUTES, &count);
  printf("Active Attributes: %d\n", count);
  for (i = 0; i < count; i++) {
    GLAttribute attribute{};

    glGetActiveAttrib(handle(), i, buf_size, &length, &attribute.size, &type,
                      name.data());
    attribute.type = GLTypeFromGlEnum(type);
    attribute.location = glGetAttribLocation(handle(), name.data());
    attribute.name = std::string{name.data()};

    printf("Attribute #%d name=%s type=%u size=%d location=%d\n", i,
           attribute.name.c_str(), attribute.type, attribute.size,
           attribute.location);

    var_attributes_.emplace(attribute.name, attribute);
  }

  // Discover the uniforms
  glGetProgramiv(handle(), GL_ACTIVE_UNIFORMS, &count);
  for (i = 0; i < count; i++) {
    GLUniform uniform{};
    glGetActiveUniform(handle(), i, buf_size, &length, &uniform.size, &type,
                       name.data());
    uniform.type = GLTypeFromGlEnum(type);
    uniform.name = std::string{name.data()};
    uniform.location = glGetUniformLocation(handle(), name.data());
    var_uniforms_.emplace(uniform.name, uniform);
  }
}

auto GLProgram::use() const noexcept -> bool {
  if (handle() > 0) {
    glUseProgram(handle());
  } else {
    std::cerr << "WebGLProgram can't use" << handle() << std::endl;
  }
  return handle() != 0U;
}

void GLProgram::apply_uniforms() const {
  for (auto u : var_uniforms_) {
    u.second.apply();
  }
}

// auto WebGLProgram::get_uniform(const std::string &name) const
//     -> const GLUniform * {
//   if (!var_uniforms_.contains(name)) {
//     return nullptr;
//   }
//   return &var_uniforms_.at(name);
// }

auto GLProgram::get_uniform(const std::string &name) -> GLUniform * {
  if (!var_uniforms_.contains(name)) {
    return nullptr;
  }
  return &var_uniforms_.at(name);
}

}  // namespace app