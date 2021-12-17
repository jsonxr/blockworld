//
// Created by Jason Rowland on 12/15/21.
//

#include "ShaderMaterial.h"

const char *vertexShaderSource =
#ifdef __EMSCRIPTEN__
    "#version 300 es\n"
#else
    "#version 330 core\n"
#endif
    "layout (location = 0) in highp vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
#ifdef __EMSCRIPTEN__
    "#version 300 es\n"
#else
    "#version 330 core\n"
#endif
    "    out highp vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "  FragColor = vec4(1.0f, 0.2f, 0.2f, 1.0f);\n"
    "}\n";

namespace BlockWorld {}
