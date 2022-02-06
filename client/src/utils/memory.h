#ifndef APP_UTILS_MEMORY_H
#define APP_UTILS_MEMORY_H

#include <string>

namespace utils {

void display_sizeof_values();

auto getTotalSystemMemory() -> size_t;

/**
 * Prints to the provided buffer a nice number of bytes (KB, MB, GB, etc)
 * Adapted from https://www.mbeckler.org/blog/?p=114
 * @param bytes
 * @return
 */
auto prettyBytes(size_t bytes) -> std::string;

}
#endif // APP_UTILS_MEMORY_H