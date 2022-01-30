#include "core/textures/TextureAtlas.h"

#include <fmt/format.h>

#include "core.h"
#include "core/Assets.h"

namespace block_world {

//------------------------------------------------------------------------------
// TexturePacker
//------------------------------------------------------------------------------
// Perhaps, do this more efficiently by using rectangles of available pixels...
// https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Rectangle_difference

struct Position {
  uint16 x;
  uint16 y;
};

void sortTextureRects(std::vector<TextureRect> &rects) {
  // Sort largest to smallest since larger are harder to place
  std::sort(rects.begin(), rects.end(), [](TextureRect &r1, TextureRect &r2) {
    // Sort by height, then by width, then by filename
    return r1.height == r2.height ? r1.width == r2.width
                                        ? r1.path.compare(r2.path) < 0
                                        : r1.width > r2.width
                                  : r1.height > r2.height;
  });
}

auto checkPosition(const TextureAtlas &atlas, const TextureRect &texture,
                   const TextureGrid &used, const Position &pos) -> bool {
  uint16 pos_x = pos.x;
  uint16 pos_y = pos.y;
  uint16 out_x_slots = atlas.get_width() / atlas.get_min_size();
  uint16 out_y_slots = atlas.get_height() / atlas.get_min_size();

  uint16 y_slots = texture.height / atlas.get_min_size() +
                   std::min(1, texture.height % atlas.get_min_size());
  uint16 x_slots = texture.width / atlas.get_min_size() +
                   std::min(1, texture.width % atlas.get_min_size());

  if ((pos_x + x_slots > out_x_slots) || (pos_y + y_slots > out_y_slots)) {
    return false;
  }

  bool open = true;
  for (uint16 y = 0; y < y_slots; y++) {
    for (uint16 x = 0; x < x_slots; x++) {
      int offset = ((pos_y + y) * out_x_slots) + (pos_x + x);
      open = open && (used.at(offset) == 0);
    }
  }
  return open;
}

void markPosition(const TextureAtlas &atlas, TextureRect &texture,
                  TextureGrid &used, const Position &pos) {
  uint16 y_slots = texture.height / atlas.get_min_size() +
                   std::min(1, texture.height % atlas.get_min_size());
  uint16 x_slots = texture.width / atlas.get_min_size() +
                   std::min(1, texture.width % atlas.get_min_size());

  uint16 pos_x = pos.x;
  uint16 pos_y = pos.y;

  uint16 out_x_slots = atlas.get_width() / atlas.get_min_size();
  uint16 out_y_slots = atlas.get_height() / atlas.get_min_size();

  for (uint16 y = 0; y < y_slots; y++) {
    for (uint16 x = 0; x < x_slots; x++) {
      int offset = ((pos_y + y) * out_x_slots) + (pos_x + x);
      used.at(offset) = texture.id;
    }
  }
}

auto findPosition(const TextureAtlas &atlas, const TextureRect &texture,
                  const TextureGrid &used) -> std::optional<Position> {
  uint16 output_y_slots =
      atlas.get_height() / atlas.get_min_size() +
      std::min(1, atlas.get_height() % atlas.get_min_size());
  uint16 output_x_slots = atlas.get_width() / atlas.get_min_size() +
                          std::min(1, atlas.get_width() % atlas.get_min_size());

  for (uint16 y = 0; y < output_y_slots; y++) {
    for (uint16 x = 0; x < output_x_slots; x++) {
      Position pos{x, y};
      if (checkPosition(atlas, texture, used, pos)) {
        return pos;
      }
    }
  }

  return std::nullopt;
}

auto setPositionsForRegions(const TextureAtlas &atlas,
                            std::vector<TextureRect> &regions)
    -> std::unique_ptr<TextureGrid> {
  int slots = (atlas.get_width() * atlas.get_height()) / atlas.get_min_size();
  auto used = std::make_unique<TextureGrid>(slots);
  // TextureGrid used(slots);

  for (auto &r : regions) {
    auto pos = findPosition(atlas, r, *used);
    if (!pos) {
      std::cout << "Could not find room for " << r.path.filename().string()
                << std::endl;
      continue;
    }

    r.x = pos->x * atlas.get_min_size();
    r.y = pos->y * atlas.get_min_size();
    float ux = static_cast<float>(r.x) / static_cast<float>(atlas.get_width());
    float uy = static_cast<float>(r.y) / static_cast<float>(atlas.get_height());
    float vx = static_cast<float>(r.x + r.width) /
               static_cast<float>(atlas.get_width());
    float vy = static_cast<float>(r.y + r.height) /
               static_cast<float>(atlas.get_height());
    r.uv = {{ux, uy}, {vx, vy}};
    markPosition(atlas, r, *used, *pos);
  }

  return used;
}

void copyPixels(const TextureAtlas &atlas, const TextureRect &texture,
                TexturePixels &pixels) {
  // Image
  auto image = std::make_unique<Image>(texture.path);

  for (uint16 y = 0; y < texture.height; y++) {
    int offset = y * texture.width * kChannels;
    unsigned char *current_raw_pixel = &image->get_pixels()[offset];

    int calc_y = (texture.y) + y;
    int y_offset = calc_y * atlas.get_width();
    int x_offset = texture.x;
    int byte_offset = y_offset + x_offset;

    if (byte_offset < pixels.size()) {
      Pixel &current_pixel = pixels[byte_offset];

      // DANGER... Bug prone memcpy here...
      memcpy(&current_pixel, current_raw_pixel, sizeof(Pixel) * texture.width);
    } else {
      std::cout << "out of range" << std::endl;
    }
  }
}

void outputTextureGrid(TextureAtlas &atlas) {
  auto used = atlas.pack();
  std::string display;

  uint16 output_y_slots =
      atlas.get_height() / atlas.get_min_size() +
      std::min(1, atlas.get_height() % atlas.get_min_size());
  uint16 output_x_slots = atlas.get_width() / atlas.get_min_size() +
                          std::min(1, atlas.get_width() % atlas.get_min_size());

  for (uint16 i = 0; i < output_y_slots; i++) {
    for (uint16 j = 0; j < output_x_slots; j++) {
      int offset = (i * output_x_slots) + j;
      if (used->at(offset) == 0) {
        display += fmt::format("{:>4} ", "");
      } else {
        display += fmt::format("{:>4} ", used->at(offset));
      };
    }
    display += "\n";
  }

  std::cout << display << std::endl;
}

//------------------------------------------------------------------------------
// TextureAtlas
//------------------------------------------------------------------------------

auto TextureAtlas::add(TextureRect &&region) -> uint16 {
  region.id = regions_.size();
  regions_.emplace_back(region);
  return region.id;
}

auto TextureAtlas::pack() -> std::unique_ptr<TextureGrid> {
  sortTextureRects(regions_);
  auto used = setPositionsForRegions(*this, regions_);
  return used;
}

auto TextureAtlas::generatePixels() -> std::unique_ptr<TexturePixels> {
  auto used = pack();
  int size = width_ * height_;
  auto pixels = std::make_unique<TexturePixels>(size);

  // Copy the pixels from the source to the destinatioon
  for (auto const &r : regions_) {
    copyPixels(*this, r, *pixels);
  }
  return pixels;
}

auto TextureAtlas::compile() -> GLuint {
  auto pixels = this->generatePixels();
  // glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &handle_);
  glBindTexture(GL_TEXTURE_2D, handle_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, pixels->data());
  glBindTexture(GL_TEXTURE_2D, NULL);  // reset
  return handle_;
}

void TextureAtlas::save(const std::string &filename) {
  auto pixels = this->generatePixels();
  int size = width_ * static_cast<int>(sizeof(Pixel));
  stbi_write_png(filename.c_str(), width_, height_, 4, pixels->data(), size);
}

auto TextureAtlas::getRectByName(const std::string &name)
    -> std::optional<TextureRect> {
  auto it = std::find_if(
      regions_.begin(), regions_.end(),
      [&name](const TextureRect &rect) { return rect.name == name; });
  if (it != regions_.end()) {
    return *it;
  }
  return std::nullopt;
}

auto TextureAtlas::loadFromDirectory(const std::string &prefix,
                                     const std::string &path, const Size size)
    -> std::unique_ptr<TextureAtlas> {
  auto atlas = std::make_unique<TextureAtlas>(size.width, size.height);
  Assets::forEachFile(
      path, ".+\\.png",
      [&atlas, &prefix](const std::filesystem::path &filepath) {
        auto image = std::make_unique<block_world::Image>(filepath);
        std::string name = prefix + image->get_path().stem().string();
        block_world::TextureRect rect{};
        rect.name = name;
        rect.path = image->get_path();
        rect.width = image->get_width();
        rect.height = image->get_height();
        atlas->add(std::move(rect));
      });
  atlas->generatePixels();
  return atlas;
}

}  // namespace block_world
