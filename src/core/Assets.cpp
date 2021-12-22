//
// Created by Jason Rowland on 12/22/21.
//
#include "Assets.h"

namespace BlockWorld {

constexpr const char *ASSETS_FILENAME =
    isEMSCRIPTEN ? "/assets" : "../../assets";

auto Assets::load(std::string filename) -> std::unique_ptr<ImagePng> {
  std::string fullFilename{ASSETS_FILENAME};
  fullFilename += filename;
  std::cout << "load filename=" << fullFilename << std::endl;

  int width{};
  int height{};
  int channels{};
  auto *ptr = stbi_load(fullFilename.c_str(), &width, &height, &channels, 0);

  //  stbi_image_free(ptr);
  //  std::cout << "freed!" << std::endl;

  auto png = std::make_unique<ImagePng>();
  png->height = height;
  png->width = width;
  png->channels = channels;
  png->data = ptr;
  return png;
}

}  // namespace BlockWorld