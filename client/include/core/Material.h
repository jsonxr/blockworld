#ifndef BLOCK_WORLD_MATERIAL_H
#define BLOCK_WORLD_MATERIAL_H

#include "Camera.h"
#include "textures/TextureAtlas.h"
#include "webgl/WebGLProgram.h"

namespace block_world {

class Material {
 public:
  explicit Material(std::unique_ptr<TextureAtlas> textures);
  ~Material() = default;
  void setModelMatrix(const mat4 model) const {
    block_world::WebGLProgram::set_uniform(loc_model_, model);
  }
  void render(Camera &camera);

  // Copy: not supported
  Material(const Material &other) = delete;        // copy constructor
  auto operator=(const Material &other) = delete;  // copy assignment
  // Move
  Material(Material &&other) noexcept
      : program_(std::exchange(other.program_, WebGLProgram{})),
        textures_(std::exchange(other.textures_, nullptr)),
        texture_(std::exchange(other.texture_, 0)),
        loc_model_(std::exchange(other.loc_model_, 0)),
        loc_texture0_(std::exchange(other.loc_texture0_, 0)),
        loc_view_(std::exchange(other.loc_view_, 0)),
        loc_projection_(std::exchange(other.loc_projection_, 0)){};
  auto operator=(Material &&other) noexcept -> Material & {
    std::swap(program_, other.program_);
    std::swap(textures_, other.textures_);
    std::swap(texture_, other.texture_);
    std::swap(loc_model_, other.loc_model_);
    std::swap(loc_texture0_, other.loc_texture0_);
    std::swap(loc_view_, other.loc_view_);
    std::swap(loc_projection_, other.loc_projection_);
    return *this;
  }

 private:
  WebGLProgram program_{};
  GLuint texture_{};
  std::unique_ptr<TextureAtlas> textures_{};
  int loc_model_{};
  int loc_texture0_{};
  int loc_view_{};
  int loc_projection_{};
};

}  // namespace block_world

#endif  // BLOCK_WORLD_MATERIAL_H
