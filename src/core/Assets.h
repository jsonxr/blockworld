//
// Created by Jason Rowland on 12/22/21.
//

#ifndef BLOCKWORLD_ASSETS_H
#define BLOCKWORLD_ASSETS_H

#include "../core.h"
#include "stb_image.h"

namespace BlockWorld {

struct ImagePng {
 public:
  int height{};
  int width{};
  int channels{};
  unsigned char* data{nullptr};

  ImagePng(){};
  ~ImagePng() {
    if (data != nullptr) {
      stbi_image_free(data);
    }
  };
  // Copy: not supported
  ImagePng(const ImagePng& other) = delete;        // copy constructor
  auto operator=(const ImagePng& other) = delete;  // copy assignment
  // Move
  ImagePng(ImagePng&& other) noexcept
      : height(std::exchange(other.height, 0)),
        width(std::exchange(other.width, 0)),
        channels(std::exchange(other.channels, 0)),
        data(std::exchange(other.data, nullptr)){};  // move
  auto operator=(ImagePng&& other) noexcept -> ImagePng& {
    std::swap(height, other.height);
    std::swap(width, other.width);
    std::swap(channels, other.channels);
    std::swap(data, other.data);
    return *this;
  }
};

class Assets {
 public:
  static auto load(std::string filename) -> std::unique_ptr<ImagePng>;
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_ASSETS_H
