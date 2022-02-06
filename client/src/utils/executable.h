#ifndef APP_UTILS_EXECUTABLE_H
#define APP_UTILS_EXECUTABLE_H

#include <filesystem>
#include <string>

namespace utils {

// Don't remember where I got this code from...
// It wasn't https://stackoverflow.com/questions/1528298/get-path-of-executable

auto get_executable_dir() -> std::filesystem::path;
auto get_executable_path() -> std::string;

}  // namespace utils

#endif  // APP_UTILS_EXECUTABLE_H
