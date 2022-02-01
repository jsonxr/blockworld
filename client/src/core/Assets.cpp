#include "core/Assets.h"

#include <fstream>
#include <iostream>
#include <regex>

#include "utils.h"

namespace app {

namespace fs = std::filesystem;

const std::string kDir =
#ifdef __EMSCRIPTEN__
    "";
#else
    get_executable_dir();
#endif

const std::string kAssetsFilename = kDir + "/assets";

auto Assets::getAbsolutePath(const std::string &path) -> std::string {
  std::string full_filename = kAssetsFilename + path;
  return full_filename;
}

// auto Assets::getFiles(const std::string &path,
//                       std::optional<const std::regex> regex)
//     -> std::vector<std::filesystem::path> {
//   std::vector<std::filesystem::path> files_in_directory{};
//   for (const auto &file : fs::directory_iterator(getAbsolutePath(path))) {
//     std::string filename = file.path().string();
//     if (!regex || std::regex_match(filename, *regex)) {
//       files_in_directory.emplace_back(file.path());
//     }
//   }
//   std::sort(files_in_directory.begin(), files_in_directory.end());
//   return files_in_directory;
// }

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

// auto Assets::getFilename(const std::string &filename) -> std::string {
//   return getAbsolutePath(filename);
// }

auto Assets::loadImages(const std::string &path)
    -> std::vector<std::unique_ptr<Image>> {
  std::vector<std::unique_ptr<Image>> images{};
  forEachFile(path, ".+\\.png",
              [&images](const std::filesystem::path &filepath) {
                auto image = std::make_unique<Image>(filepath);
                images.emplace_back(std::move(image));
              });
  return images;
}

auto Assets::loadImage(const std::string &filename) -> std::unique_ptr<Image> {
  auto full_filename = getAbsolutePath(filename);
  std::cout << "load filename=" << full_filename << std::endl;
  auto png = std::make_unique<Image>(full_filename);
  return png;
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