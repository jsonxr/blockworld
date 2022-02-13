/**
 * @file test.cpp
 * @author your name (you@domain.com)
 * @brief Demonstrates how to set/get from bit masks.
 * @version 0.1
 * @date 2022-02-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>

using std::cout;
using std::endl;

auto main(int /*argc*/, char ** /*argv*/, char **envp) -> int {
  // 16bit masks
  constexpr uint16_t mask_textureid{0b1111'1111'1111'0000};
  constexpr uint16_t mask_face_normal{0b0000'0000'0000'1110};
  constexpr uint16_t mask_biome_blend{0b0000'0000'0000'0001};

  // 2nd 32bits
  constexpr uint32_t mask_rgb{0b1111'1111'1111'1111'1111'1111'0000'0000};
  constexpr uint32_t mask_lightlevel{0b0000'0000'0000'0000'0000'0000'1111'0000};
  constexpr uint32_t mask_rotation{0b0000'0000'0000'0000'0000'0000'0000'1100};

  uint32_t thecolor = 0xf0000f;
  cout << "thecolor=" << std::hex << thecolor << endl;

  uint32_t two{};
  uint32_t in_rgb = (thecolor << 8) & mask_rgb;
  uint32_t in_lightLevel = (13 << 4) & mask_lightlevel;
  uint32_t in_rotation = (3 << 2) & mask_rotation;

  two = in_rgb | in_lightLevel | in_rotation;

  uint32_t out_rgb{static_cast<std::uint32_t>((two & mask_rgb) >> 8)};
  uint32_t out_light{static_cast<std::uint8_t>((two & mask_lightlevel) >> 4)};
  uint32_t out_rot{static_cast<std::uint8_t>((two & mask_rotation) >> 2)};

  cout << out_rgb << "," << out_light << "," << out_rot << endl;
}
