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
  explicit Image(std::filesystem::path path);
  ~Image();
  [[maybe_unused]] [[nodiscard]] auto channels() const -> int;
  [[maybe_unused]] [[nodiscard]] auto path() -> const std::filesystem::path &;
  [[maybe_unused]] [[nodiscard]] auto height() const -> int;
  [[maybe_unused]] [[nodiscard]] auto width() const -> int;
  [[maybe_unused]] [[nodiscard]] auto pixels() const -> unsigned char *;
  [[maybe_unused]] [[nodiscard]] auto get_size() const -> int;

  Image() = default;
  Image(const Image &other) = delete;           // copy constructor
  auto operator=(const Image &other) = delete;  // copy assignment
  Image(Image &&other) noexcept;                // move constructor
  auto operator=(Image &&other) noexcept -> Image &;

 private:
  std::filesystem::path path_;
  int channels_{};
  int height_{};
  int width_{};
  unsigned char *pixels_ = nullptr;
};

}  // namespace app

#endif  // APP_TEXTURES_IMAGE_H
