#ifndef APP_TEXTURES_IMAGE_H
#define APP_TEXTURES_IMAGE_H

#include <stb_image.h>
#include <stb_image_write.h>

#include <filesystem>
#include <string>
#include <utility>

#include "Pixel.h"

namespace app {

constexpr auto isPowerOf2(int value) -> bool {
  // value can't be zero
  // use bitwise AND because...
  // 16: 1 0000 & 15 = 0 0000 // Power of 2
  // 15: 0 1111 & 14 = 0 1110
  // 14: 0 1110 & 13 = 0 1100
  // 13: 0 1101 & 12 = 0 1100
  // 12: 0 1100 & 11 = 0 1000
  // 11: 0 1011 & 10 = 0 1010
  // 10: 0 1010 & 9  = 0 1000
  //  9: 0 1001 & 8  = 0 1000
  //  8: 0 1000 & 7  = 0 0000 // Power of 2
  //  7: 0 0111
  return (value != 0) && ((value & (value - 1)) == 0);
}

class Image {
 public:
  explicit Image(std::filesystem::path path)
      : path_(std::move(path)),
        pixels_(stbi_load(path_.c_str(), &width_, &height_, &channels_,
                          kChannels)){};
  ~Image() {
    channels_ = 0;
    height_ = 0;
    width_ = 0;
    path_ = "";
    if (pixels_ != nullptr) {
      stbi_image_free(pixels_);
      pixels_ = nullptr;
    }
  };

  [[nodiscard]] auto get_channels() const -> int { return channels_; }
  [[nodiscard]] auto get_path() -> const std::filesystem::path & {
    return path_;
  }
  [[nodiscard]] auto get_height() const -> int { return height_; }
  [[nodiscard]] auto get_width() const -> int { return width_; }
  [[nodiscard]] auto get_pixels() const -> unsigned char * { return pixels_; }
  [[nodiscard]] auto get_size() const -> int {
    return width_ * height_ * kChannels;
  }

  // Copy: not supported
  Image() = default;
  Image(const Image &other) = delete;           // copy constructor
  auto operator=(const Image &other) = delete;  // copy assignment
  // Move
  Image(Image &&other) noexcept
      : path_(std::exchange(other.path_, std::filesystem::path{})),
        pixels_(std::exchange(other.pixels_, nullptr)),
        channels_(std::exchange(other.channels_, 0)),
        height_(std::exchange(other.height_, 0)),
        width_(std::exchange(other.width_, 0)){};  // move constructor
  auto operator=(Image &&other) noexcept -> Image & {
    std::swap(path_, other.path_);
    std::swap(pixels_, other.pixels_);
    std::swap(channels_, other.channels_);
    std::swap(height_, other.height_);
    std::swap(width_, other.width_);
    return *this;
  };

 private:
  std::filesystem::path path_;
  int channels_{};
  int height_{};
  int width_{};
  unsigned char *pixels_ = nullptr;
};

}  // namespace app

#endif  // APP_TEXTURES_IMAGE_H
