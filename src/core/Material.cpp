//
// Created by Jason Rowland on 12/17/21.
//

#include "Material.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

namespace BlockWorld {

// const char *vertexShaderSourcesave =
//#ifdef __EMSCRIPTEN__
//     "#version 300 es\n"
//#else
//     "#version 330 core\n"
//#endif
//     "layout (location = 0) in highp vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";

// const char *fragmentShaderSourcesave =
//#ifdef __EMSCRIPTEN__
//     "#version 300 es\n"
//#else
//     "#version 330 core\n"
//#endif
//     "    out highp vec4 FragColor;\n"
//
//     "uniform highp vec4 ourColor;\n"  // we set this variable in the OpenGL
//                                       // code.
//
//     "\n"
//     "void main()\n"
//     "{\n"
//     //"  FragColor = vec4(1.0f, 0.2f, 0.2f, 1.0f);\n"
//     "  FragColor = ourColor;\n"
//     "}\n";

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
  std::string vertexShaderSource = readAssetIntoString("/vertex.glsl");
  std::string fragmentShaderSource = readAssetIntoString("/fragment.glsl");
  // std::cout << file_contents << std::endl;

  WebGLShader vertexShader{WebGLShaderType::vertex, vertexShaderSource.c_str()};
  WebGLShader fragmentShader{WebGLShaderType::fragment,
                             fragmentShaderSource.c_str()};
  _program = WebGLProgram{vertexShader, fragmentShader};
}

}  // namespace BlockWorld
