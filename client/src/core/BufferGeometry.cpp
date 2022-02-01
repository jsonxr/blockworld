#include "core/BufferGeometry.h"

#include <bit>
#include <iostream>
#include <vector>

namespace app {

BufferGeometry::BufferGeometry(BufferGeometry &&other) noexcept
    : glVao_(std::exchange(other.glVao_, 0)),
      glVbo_(std::exchange(other.glVbo_, 0)),
      count_(std::exchange(other.count_, 0)){};  // move

auto BufferGeometry::operator=(BufferGeometry &&other) noexcept
    -> BufferGeometry & {
  std::swap(glVao_, other.glVao_);
  std::swap(glVbo_, other.glVbo_);
  std::swap(count_, other.count_);
  return *this;
}

auto sizeofGlType(GLenum t) -> int {
  if (t == GL_BYTE) return sizeof(GLbyte);
  if (t == GL_UNSIGNED_BYTE) return sizeof(GLubyte);
  if (t == GL_SHORT) return sizeof(GLshort);
  if (t == GL_UNSIGNED_SHORT) return sizeof(GLushort);
  if (t == GL_INT) return sizeof(GLint);
  if (t == GL_UNSIGNED_INT) return sizeof(GLuint);
  // if (t == GL_FIXED) return sizeof(GLfixed);
  if (t == GL_HALF_FLOAT) return sizeof(GLhalf);
  if (t == GL_FLOAT) return sizeof(GLfloat);
  if (t == GL_DOUBLE) return sizeof(GLdouble);
  return 0;
}

BufferGeometry::BufferGeometry(const std::vector<GLfloat> &vertices,
                               const std::vector<BufferAttribute> &attributes) {
  // std::array<BufferAttribute, 2> attributes2{{
  //     {.type = GL_FLOAT, .size = sizeof(GLfloat), .count = 3},  // position
  //     {.type = GL_FLOAT, .size = sizeof(GLfloat), .count = 2}   // uv
  // }};

  // geometry.setAttribute( 'position', new THREE.BufferAttribute( vertices, 3 )
  // geometry.setAttribute( 'color', new THREE.BufferAttribute( vertices, 3 )
  // geometry.setAttribute( 'uv', new THREE.BufferAttribute( vertices, 2 ) );

  int size = static_cast<GLint>(vertices.size() * sizeof(GLfloat));
  if (size < 0) {
    std::cerr << "Nothing in the mesh to compile. skipping..." << std::endl;
    return;
  }

  int stride = 0;
  for (const auto &a : attributes) {
    stride += a.count * sizeofGlType(a.type);
  }

  count_ = (GLsizei)size / stride;

  glGenVertexArrays(1, &glVao_);
  glBindVertexArray(glVao_);

  glGenBuffers(1, &glVbo_);
  glBindBuffer(GL_ARRAY_BUFFER, glVbo_);
  glBufferData(GL_ARRAY_BUFFER, size, vertices.data(),  // NOLINT
               GL_STATIC_DRAW);

  // HALF_FLOAT Maybe a half float for these texture coordinates between 0 and
  // 1?
  // Can we pass in 4 bytes as the rgba color for a vertex coordinate to cut
  // down on size? r,g,b,a = 0-255 (1byte)

  int index = 0;
  long offset = 0;
  for (const auto &a : attributes) {
    const GLvoid *offset_ptr = (GLvoid *)offset;  // NOLINT
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, a.count, a.type, GL_FALSE, stride, offset_ptr);
    // Ready the state for the next attribute
    offset += static_cast<long>(sizeofGlType(a.type) * a.count);
    index++;
  }

  glBindVertexArray(NULL);
}

BufferGeometry::~BufferGeometry() noexcept {
  if (glVao_ > 0) {
    glDeleteVertexArrays(1, &glVao_);
    glVao_ = 0;
  }
  if (glVbo_ > 0) {
    glDeleteBuffers(1, &glVbo_);
    glVbo_ = 0;
  }
}

void BufferGeometry::render() const {
  glBindVertexArray(glVao_);  // Is this even needed?
  glDrawArrays(GL_TRIANGLES, 0, count_);
  //  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}

}  // namespace app
