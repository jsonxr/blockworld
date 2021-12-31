#ifndef BLOCKWORLD_ASSETS_H
#define BLOCKWORLD_ASSETS_H

#include "../core.h"
#include "stb_image.h"

namespace BlockWorld {

class AssetPng {
 public:
  [[nodiscard]] auto height() const -> int { return _height; };
  [[nodiscard]] auto width() const -> int { return _width; };
  [[nodiscard]] auto channels() const -> int { return _channels; };
  [[nodiscard]] auto data() const -> unsigned char* { return _data; };

  AssetPng() = default;
  explicit AssetPng(const char* filename) {
    stbi_set_flip_vertically_on_load(1);
    _data = stbi_load(filename, &_width, &_height, &_channels, 0);
  }
  ~AssetPng() {
    if (_data != nullptr) {
      std::cout << "AssetPng free data" << std::endl;
      stbi_image_free(_data);
      _data = nullptr;
    }
  };
  // Copy: not supported
  AssetPng(const AssetPng& other) = delete;        // copy constructor
  auto operator=(const AssetPng& other) = delete;  // copy assignment
  // Move
  AssetPng(AssetPng&& other) noexcept
      : _width(std::exchange(other._width, 0)),
        _height(std::exchange(other._height, 0)),
        _channels(std::exchange(other._channels, 0)),
        _data(std::exchange(other._data, nullptr)){};  // move
  auto operator=(AssetPng&& other) noexcept -> AssetPng& {
    std::swap(_width, other._width);
    std::swap(_height, other._height);
    std::swap(_channels, other._channels);
    std::swap(_data, other._data);
    return *this;
  }

 private:
  int _height{};
  int _width{};
  int _channels{};
  unsigned char* _data{nullptr};
};

class Assets {
 public:
  static auto loadPng(const char* filename) -> std::unique_ptr<AssetPng>;
  static auto loadString(const char* filename) -> std::string;
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_ASSETS_H
