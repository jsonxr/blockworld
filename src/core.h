#ifndef BLOCK_WORLD_CORE_H
#define BLOCK_WORLD_CORE_H

#include "vendor/glfw.h"
#include "vendor/glm.h"

// Standard library stuff
#include <array>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;

constexpr int MAX_LOG_LENGTH = 1024;

#ifdef __EMSCRIPTEN__
constexpr auto isEMSCRIPTEN() -> bool { return true; }
#else
constexpr auto isEMSCRIPTEN() -> bool { return false; }
#endif

#endif  // BLOCK_WORLD_CORE_H
