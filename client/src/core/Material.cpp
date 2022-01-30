#include "core/Material.h"

#include <iostream>
#include <regex>

#include "core/Assets.h"
#include "core/Window.h"

namespace block_world {

auto readAssetIntoString(const char *filename) -> std::string {
  std::string contents = Assets::loadString(filename);

  if (kIsEmScripten) {
    static const std::regex kOpenglVersion{"#version 330 core"};
    contents = std::regex_replace(contents, kOpenglVersion,
                                  "#version 300 es\n#define EMSCRIPTEN");
  }

  return contents;
}

Material::Material(std::unique_ptr<TextureAtlas> textures)
    : textures_(std::move(textures)) {
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

  // // texture
  // if (textureFilename == nullptr) {
  //   return;
  // }

  // auto png = Assets::loadImage(textureFilename);
  // std::cout << "data: "
  //           << "texture=" << textureFilename << " height=" << png->height()
  //           << " width=" << png->width() << " channels=" << png->channels()
  //           << std::endl;
  // // Performance, make sure we only use power of 2 textures
  // if (!isPowerOf2(png->width()) || !isPowerOf2(png->height())) {
  //   std::cerr << "image not power of 2" << std::endl;
  //   exit(EXIT_FAILURE);
  // }

  // glGenTextures(1, &texture_);
  // // ??? glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, texture_);

  // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
  // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // // glGenerateMipmap(GL_TEXTURE_2D);
  // //_gl.SRGB8_ALPHA8 : _gl.RGBA8

  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, png->width(), png->height(), 0,
  //              GL_RGBA, GL_UNSIGNED_BYTE, png->data());
  // glBindTexture(GL_TEXTURE_2D, NULL);  // reset

  // // if non power of 2
  // //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  // //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // // else mipmap
  // // glGenerateMipmap(GL_TEXTURE_2D);

  // // glBindTexture(GL_TEXTURE_2D, NULL);
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

  //  mat4 projection = glm::perspective(
  //      glm::radians(45.0F), (float)kDefaultWindowWidth /
  //      (float)kDefaultWindowHeight, 0.1F, 100.0F);
  auto projection = camera.get_projection_matrix();
  WebGLProgram::set_uniform(loc_projection_, projection);
}

}  // namespace block_world
