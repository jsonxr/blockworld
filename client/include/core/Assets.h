#ifndef APP_ASSETS_H
#define APP_ASSETS_H

#include <filesystem>
#include <map>
#include <optional>
#include <regex>

#include "core.h"
#include "stb_image.h"
#include "textures/Image.h"

namespace app {

class Assets {
 public:
  static auto getAbsolutePath(const std::string &path) -> std::string;
  // static auto getFiles(const std::string &path,
  //                      std::optional<const std::regex> regex = std::nullopt)
  //     -> std::vector<std::filesystem::path>;

  static void forEachFile(const std::string &path,
                          std::optional<const std::string> regex,
                          const std::function<void(std::filesystem::path)> &fn);

  static auto loadImages(const std::string &path)
      -> std::vector<std::unique_ptr<Image>>;

  // [[deprecated("Replaced by getAbsolutePath")]] static auto getFilename(
  //     const std::string &filename) -> std::string;

  // static auto loadImage(const std::string &filename) -> Image;
  static auto loadImage(const std::string &filename) -> std::unique_ptr<Image>;
  static auto loadString(const std::string &filename) -> std::string;
};

}  // namespace app

#endif  // APP_ASSETS_H
