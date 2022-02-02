#include "Material.h"

#include <cstdarg>
#include <iostream>
#include <regex>

#include "Assets.h"
#include "Logger.h"
#include "Window.h"

namespace app {

static Logger log{"Material.cpp"};

auto readAssetIntoString(const char *filename) -> std::string {
  std::string contents = Assets::loadString(filename);

  if (kIsEmScripten) {
    static const std::regex kOpenglVersion{"#version 330 core"};
    contents = std::regex_replace(contents, kOpenglVersion,
                                  "#version 300 es\n#define EMSCRIPTEN");
  }

  return contents;
}

Material::Material(std::shared_ptr<TextureAtlas> textures)
    : textures_{std::move(textures)} {
  std::string vertex_shader_source =
      readAssetIntoString("/shaders/vertex.glsl");
  std::string fragment_shader_source =
      readAssetIntoString("/shaders/fragment.glsl");

  WebGLShader vertex_shader{WebGLShaderType::kVertex,
                            vertex_shader_source.c_str()};
  WebGLShader fragment_shader{WebGLShaderType::kFragment,
                              fragment_shader_source.c_str()};
  program_ = WebGLProgram{vertex_shader, fragment_shader};

  // Get locations of uniforms for vertex/fragment shaders
  loc_model_ = program_.get_uniform_location("model");
  loc_texture0_ = program_.get_uniform_location("texture0");
  loc_view_ = program_.get_uniform_location("view");
  loc_projection_ = program_.get_uniform_location("projection");

  texture_ = textures_->compile();
}

void Material::render(Camera &camera) {
  if (!program_.use()) {
    std::cerr << "WebGLMaterial::use program not available" << std::endl;
    return;
  }

  if (texture_ != 0) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_);
    WebGLProgram::set_uniform(loc_texture0_, 0);  // GL_TEXTURE0
  }

  auto view = camera.get_view_matrix();
  WebGLProgram::set_uniform(loc_view_, view);
  // kLogger("from logger...", 42);
  // std::cout << "view=" << view << std::endl;

  //  mat4 projection = glm::perspective(
  //      glm::radians(45.0F), (float)kDefaultWindowWidth /
  //      (float)kDefaultWindowHeight, 0.1F, 100.0F);
  auto projection = camera.get_projection_matrix();
  WebGLProgram::set_uniform(loc_projection_, projection);
}

}  // namespace app
