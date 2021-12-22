//
// Created by Jason Rowland on 12/17/21.
//

#include "Material.h"

#include <fstream>
#include <iostream>
#include <regex>

#include "Assets.h"

namespace BlockWorld {

auto readAssetIntoString(const std::string &path) -> std::string {
  constexpr const char *ASSETS_FILENAME =
      isEMSCRIPTEN ? "/assets" : "../../assets";

  std::string filename{ASSETS_FILENAME};
  filename += path;

  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '" << path << "'" << std::endl;
    exit(EXIT_FAILURE);
  }
  auto contents = std::string((std::istreambuf_iterator<char>(input_file)),
                              std::istreambuf_iterator<char>());

  if (isEMSCRIPTEN) {
    static const std::regex opengl_version{"#version 330 core"};
    contents = std::regex_replace(contents, opengl_version,
                                  "#version 300 es\n#define __EMSCRIPTEN__");
  }

  return contents;
}

Material::Material() {
  auto png = Assets::load("/textures/block/stone.png");
  std::cout << "data: "
            << " height=" << png->height << " width=" << png->width
            << " channels=" << png->channels << std::endl;

  std::string vertexShaderSource = readAssetIntoString("/vertex.glsl");
  std::string fragmentShaderSource = readAssetIntoString("/fragment.glsl");
  // std::cout << file_contents << std::endl;

  WebGLShader vertexShader{WebGLShaderType::vertex, vertexShaderSource.c_str()};
  WebGLShader fragmentShader{WebGLShaderType::fragment,
                             fragmentShaderSource.c_str()};
  _program = WebGLProgram{vertexShader, fragmentShader};
}

}  // namespace BlockWorld
