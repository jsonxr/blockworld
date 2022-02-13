#include "Assets.h"

#include <fstream>
#include <iostream>
#include <regex>

#include "../utils/env.h"
#include "../utils/executable.h"

namespace app {

namespace fs = std::filesystem;

auto Assets::getRootPath() -> std::string { return utils::get_assets_path(); }

auto Assets::getAbsolutePath(const std::string &path) -> std::string {
  std::string full_filename = utils::get_assets_path() + path;
  return full_filename;
}

void Assets::forEachFile(const std::string &path,
                         std::optional<const std::string> regex,
                         const std::function<void(std::filesystem::path)> &fn) {
  auto absolute_path = getAbsolutePath(path);

  for (const auto &file :
       fs::directory_iterator(std::filesystem::path{absolute_path})) {
    std::string filename = file.path().string();
    if (!regex || std::regex_match(filename, std::regex{*regex})) {
      fn(file.path());
    }
  }
}

auto Assets::loadString(const std::string &filename) -> std::string {
  auto full_filename = getAbsolutePath(filename);

  std::ifstream input_file(full_filename);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << full_filename << "'"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  auto contents = std::string((std::istreambuf_iterator<char>(input_file)),
                              std::istreambuf_iterator<char>());
  return contents;
}

}  // namespace app