#include "core/BufferGeometry.h"

#include <bit>
#include <iostream>
#include <vector>

namespace app {

void BufferGeometry::append(const BufferGeometry &v) {
  int stride = 0;
  for (auto a : attributes) {
    stride += a.count;
  }

  // size=1, index = 1
  size_t size = vertices.size() / stride;
  // Add all the vertices

  // int count = 0;
  for (auto v : v.vertices) {
    // std::cout << count << ": v=" << v << std::endl;
    vertices.emplace_back(v);
    // count++;
  }

  // Add all the indexes, but they start with size
  // count = 0;
  for (auto index : v.elements) {
    // std::cout << count << ": index=" << (size + index) << std::endl;
    elements.emplace_back(size + index);
    // count++;
  };
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

BufferGeometryGfx::BufferGeometryGfx(const BufferGeometry &geometry) {
  std::cout << "BufferGeometryGfx()" << std::endl;
  int size = static_cast<GLint>(geometry.vertices.size() * sizeof(GLfloat));
  if (size < 0) {
    std::cerr << "Nothing in the mesh to compile. skipping..." << std::endl;
    return;
  }

  int stride = 0;
  for (const auto &a : geometry.attributes) {
    stride += a.count * sizeofGlType(a.type);
  }

  count_ = (GLsizei)size / stride;

  glGenVertexArrays(1, &glVao_);
  glBindVertexArray(glVao_);

  glGenBuffers(1, &glVbo_);
  glBindBuffer(GL_ARRAY_BUFFER, glVbo_);
  glBufferData(GL_ARRAY_BUFFER, size, geometry.vertices.data(),  // NOLINT
               GL_STATIC_DRAW);

  // HALF_FLOAT Maybe a half float for these texture coordinates between 0 and
  // 1?
  // Can we pass in 4 bytes as the rgba color for a vertex coordinate to cut
  // down on size? r,g,b,a = 0-255 (1byte)

  int index = 0;
  long offset = 0;
  for (const auto &a : geometry.attributes) {
    const GLvoid *offset_ptr = (GLvoid *)offset;  // NOLINT
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, a.count, a.type, GL_FALSE, stride, offset_ptr);
    // Ready the state for the next attribute
    offset += static_cast<long>(sizeofGlType(a.type) * a.count);
    index++;
  }

  if (!geometry.elements.empty()) {
    glGenBuffers(1, &glEbo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glEbo_);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(sizeof(int) * geometry.elements.size()),
        geometry.elements.data(), GL_STATIC_DRAW);
    elements_size_ = static_cast<GLsizei>(geometry.elements.size());
  }

  glBindVertexArray(NULL);
}

BufferGeometryGfx::BufferGeometryGfx(BufferGeometryGfx &&other) noexcept
    : glVao_(std::exchange(other.glVao_, 0)),
      glVbo_(std::exchange(other.glVbo_, 0)),
      count_(std::exchange(other.count_, 0)){};  // move

auto BufferGeometryGfx::operator=(BufferGeometryGfx &&other) noexcept
    -> BufferGeometryGfx & {
  std::swap(glVao_, other.glVao_);
  std::swap(glVbo_, other.glVbo_);
  std::swap(count_, other.count_);
  return *this;
}

BufferGeometryGfx::~BufferGeometryGfx() noexcept {
  if (glVao_ > 0) {
    glDeleteVertexArrays(1, &glVao_);
    glVao_ = 0;
  }
  if (glVbo_ > 0) {
    glDeleteBuffers(1, &glVbo_);
    glVbo_ = 0;
  }
  if (glEbo_ > 0) {
    glDeleteBuffers(1, &glEbo_);
  }
}

void BufferGeometryGfx::render() const {
  if (elements_size_ == 0) {
    glBindVertexArray(glVao_);  // Is this even needed?
    glDrawArrays(GL_TRIANGLES, 0, count_);
  } else {
    glBindVertexArray(glVao_);  // Is this even needed?
    glDrawElements(GL_TRIANGLES, elements_size_, GL_UNSIGNED_INT, nullptr);
  }
}

}  // namespace app
