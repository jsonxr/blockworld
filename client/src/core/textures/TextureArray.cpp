
#include "core/textures/TextureArray.h"

#include "core/Assets.h"
#include "core/textures/Image.h"
#include "core/textures/TextureAtlas.h"

namespace block_world {

constexpr int kMipLevel = 0;
constexpr int kBorder = 0;

// auto load_texture(const std::string &filename) -> Texture {
//   auto image = std::make_unique<Image>(filename);
//   Texture texture{};
//   texture.width = image->get_width();
//   texture.height = image->get_height();
//   texture.filename = filename;
//   return texture;
// }

void TextureArray::add(const std::string &filename) {
  filenames_.emplace_back(filename);
};

auto TextureArray::compile() -> GLuint {
  auto texture_filename = filenames_[0];

  auto png = Assets::loadImage(texture_filename);
  std::cout << "data: "
            << "texture=" << texture_filename << " height=" << png->get_height()
            << " width=" << png->get_width()
            << " channels=" << png->get_channels() << std::endl;
  // Performance, make sure we only use power of 2 textures
  if (!isPowerOf2(png->get_width()) || !isPowerOf2(png->get_height())) {
    std::cerr << "image not power of 2" << std::endl;
    exit(EXIT_FAILURE);  // NOLINT(concurrency-mt-unsafe)
  }

  std::cout << "textures.cpp compile...." << std::endl;

  // glActiveTexture(GL_TEXTURE0);
  // glGenTextures(1, &handle_);
  // glBindTexture(GL_TEXTURE_2D_ARRAY, handle_);

  // glTexImage3D(GL_TEXTURE_2D_ARRAY, kMipLevel, GL_RGBA, 32, 32, 1, 0,
  // GL_RGBA,
  //              GL_UNSIGNED_BYTE, nullptr);
  // glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, 32, 32, 1, GL_RGBA,
  //                 GL_UNSIGNED_BYTE, png->get_pixels());
  // std::cout << "error " << glGetError() << std::endl;
  // glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  // glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &handle_);
  glBindTexture(GL_TEXTURE_2D, handle_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png->get_width(), png->get_height(),
               0, GL_RGBA, GL_UNSIGNED_BYTE, png->get_pixels());
  glBindTexture(GL_TEXTURE_2D, NULL);  // reset

  std::cout << "Textures: handle_ = " << handle_ << std::endl;
  return handle_;
}

}  // namespace block_world