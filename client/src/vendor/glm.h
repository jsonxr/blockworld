#pragma clang diagnostic ignored "-Wdeprecated-volatile"

#ifndef APP_GLM_H
#define APP_GLM_H

#define GLM_FORCE_CXX11

// include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// NOLINTBEGIN
#include <glm/ext.hpp>
#include <glm/gtc/type_ptr.hpp>
// NOLINTEND

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;
using ivec2 = glm::ivec2;
using ivec3 = glm::ivec3;

#endif  // APP_GLM_H
