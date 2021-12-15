#ifndef BLOCK_WORLD_TEXTURES_TEXTUREARRAY_H
#define BLOCK_WORLD_TEXTURES_TEXTUREARRAY_H

#include <vector>

#include "core.h"
#include "core/textures/Pixel.h"
#include "core/textures/Texture.h"

namespace block_world {

class TextureArray {
 public:
  void add(const std::string &filename);
  auto compile() -> GLuint;

 private:
  uint width_{32};
  uint height_{32};
  std::vector<std::string> filenames_{};
  GLuint handle_{0};
};

}  // namespace block_world

#endif  // BLOCK_WORLD_TEXTURES_TEXTUREARRAY_H
