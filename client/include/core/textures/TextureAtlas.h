#ifndef BLOCK_WORLD_TEXTURES_TEXTUREATLAS_H
#define BLOCK_WORLD_TEXTURES_TEXTUREATLAS_H

#include <optional>
#include <vector>

#include "Image.h"
#include "Texture.h"
#include "TextureRect.h"
#include "core.h"

namespace block_world {

constexpr ushort kTextureAtlasDefaultSize = 1024;
constexpr ushort kTextureAtlasMinSize = 16;

using TextureGrid = std::vector<int>;
using TexturePixels = std::vector<Pixel>;  // 4_194_304

struct Size {
  ushort width;
  ushort height;
};

class TextureAtlas {
 public:
  TextureAtlas()
      : width_(kTextureAtlasDefaultSize), height_(kTextureAtlasDefaultSize){};
  explicit TextureAtlas(ushort width, ushort height,  // NOLINT
                        ushort min_size = kTextureAtlasMinSize)
      : width_(width), height_(height), min_size_(min_size) {}

  [[nodiscard]] auto get_width() const -> ushort { return width_; }
  [[nodiscard]] auto get_height() const -> ushort { return height_; }
  [[nodiscard]] auto get_min_size() const -> ushort { return min_size_; }

  auto pack() -> std::unique_ptr<TextureGrid>;
  auto compile() -> GLuint;
  auto generatePixels() -> std::unique_ptr<TexturePixels>;
  auto add(TextureRect &&region) -> ushort;
  void save(const std::string &filename);
  auto getRectByName(const std::string &name) -> std::optional<TextureRect>;
  static auto loadFromDirectory(const std::string &prefix,
                                const std::string &filepath,
                                Size size = Size{kTextureAtlasDefaultSize,
                                                 kTextureAtlasDefaultSize})
      -> std::unique_ptr<TextureAtlas>;

 private:
  ushort min_size_{kTextureAtlasMinSize};
  ushort width_{kTextureAtlasDefaultSize};
  ushort height_{kTextureAtlasDefaultSize};
  std::vector<TextureRect> regions_{};
  GLuint handle_{0};
};

}  // namespace block_world

#endif  // BLOCK_WORLD_TEXTURES_TEXTUREATLAS_H
