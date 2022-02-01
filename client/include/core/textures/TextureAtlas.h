#ifndef APP_TEXTURES_TEXTUREATLAS_H
#define APP_TEXTURES_TEXTUREATLAS_H

#include <optional>
#include <vector>

#include "Image.h"
#include "Texture.h"
#include "TextureRect.h"
#include "core.h"

namespace app {

constexpr uint16 kTextureAtlasDefaultSize = 1024;
constexpr uint16 kTextureAtlasMinSize = 16;

using TextureGrid = std::vector<int>;
using TexturePixels = std::vector<Pixel>;  // 4_194_304

struct Size {
  uint16 width;
  uint16 height;
};

class TextureAtlas {
 public:
  TextureAtlas()
      : width_(kTextureAtlasDefaultSize), height_(kTextureAtlasDefaultSize){};
  explicit TextureAtlas(uint16 width, uint16 height,  // NOLINT
                        uint16 min_size = kTextureAtlasMinSize)
      : width_(width), height_(height), min_size_(min_size) {}

  [[nodiscard]] auto get_width() const -> uint16 { return width_; }
  [[nodiscard]] auto get_height() const -> uint16 { return height_; }
  [[nodiscard]] auto get_min_size() const -> uint16 { return min_size_; }

  auto pack() -> std::unique_ptr<TextureGrid>;
  auto compile() -> GLuint;
  auto generatePixels() -> std::unique_ptr<TexturePixels>;
  auto add(TextureRect &&region) -> uint16;
  void save(const std::string &filename);
  auto getRectByName(const std::string &name) -> std::optional<TextureRect>;
  static auto loadFromDirectory(const std::string &prefix,
                                const std::string &filepath,
                                Size size = Size{kTextureAtlasDefaultSize,
                                                 kTextureAtlasDefaultSize})
      -> std::shared_ptr<TextureAtlas>;

 private:
  uint16 min_size_{kTextureAtlasMinSize};
  uint16 width_{kTextureAtlasDefaultSize};
  uint16 height_{kTextureAtlasDefaultSize};
  std::vector<TextureRect> regions_{};
  GLuint handle_{0};
};

}  // namespace app

#endif  // APP_TEXTURES_TEXTUREATLAS_H
