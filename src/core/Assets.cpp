#include "Assets.h"

#include <fstream>
#include <iostream>
#include <regex>

namespace BlockWorld {

constexpr const char *ASSETS_FILENAME =
    isEMSCRIPTEN() ? "/assets" : "../../assets";

auto Assets::loadPng(const char *filename) -> std::unique_ptr<AssetPng> {
  std::string fullFilename{ASSETS_FILENAME};
  fullFilename += filename;
  std::cout << "load filename=" << fullFilename << std::endl;
  auto png = std::make_unique<AssetPng>(fullFilename.c_str());
  return png;
}

auto Assets::loadString(const char *filename) -> std::string {
  std::string fullFilename{ASSETS_FILENAME};
  fullFilename += filename;

  std::ifstream input_file(fullFilename);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
    exit(EXIT_FAILURE);
  }
  auto contents = std::string((std::istreambuf_iterator<char>(input_file)),
                              std::istreambuf_iterator<char>());
  return contents;
}

}  // namespace BlockWorld