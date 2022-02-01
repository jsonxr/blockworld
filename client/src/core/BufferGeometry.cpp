#include "core/BufferGeometry.h"

#include <bit>
#include <iostream>
#include <vector>

namespace app {

BufferGeometry::~BufferGeometry() {
  std::cout << "~BufferGeometry"
            << " glVao_=" << glVao_ << " glVbo_=" << glVbo_
            << " glEbo_=" << glEbo_ << std::endl;
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
    glEbo_ = 0;
  }
}

BufferGeometry::BufferGeometry(std::vector<GLfloat> vertices) noexcept
    : vertices_(std::move(vertices)) {
  std::cout << "BufferGeometry size=" << vertices_.size() << std::endl;

  // TODO(jason): Figure out how to be certain we only have max int values
  size_t vertex_size = vertices_.size() * sizeof(GLfloat);

  if (vertex_size < 0) {
    std::cerr << "Nothing in the mesh to compile. skipping..." << std::endl;
    return;
  }

  // Create Buffers

  glGenVertexArrays(1, &glVao_);
  glBindVertexArray(glVao_);

  glGenBuffers(1, &glVbo_);
  glBindBuffer(GL_ARRAY_BUFFER, glVbo_);
  glBufferData(GL_ARRAY_BUFFER, vertex_size, vertices_.data(),  // NOLINT
               GL_STATIC_DRAW);

  //  glGenBuffers(1, &glEbo_);
  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glEbo_);
  //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, _indices.data(),
  //               GL_STATIC_DRAW);

  constexpr int kStride = 5 * sizeof(GLfloat);
  constexpr GLint kLocApos = 0;
  constexpr GLint kLocTexture = 1;
  constexpr int kPositionFloats = 3;
  constexpr int kTextureFloats = 2;
  glEnableVertexAttribArray(kLocApos);     // aPos location
  glEnableVertexAttribArray(kLocTexture);  // aTexCoord location
  glVertexAttribPointer(kLocApos, kPositionFloats, GL_FLOAT, GL_FALSE, kStride,
                        static_cast<GLvoid *>(nullptr));

  const auto *offset_texture =
      (const GLvoid *)(kPositionFloats * sizeof(GLfloat));  // NOLINT
  glVertexAttribPointer(kLocTexture, kTextureFloats, GL_FLOAT, GL_FALSE,
                        kStride, offset_texture);

  glBindVertexArray(NULL);
  std::cout << "Compiled mesh glVao_=" << glVao_ << " glVbo_=" << glVbo_
            << " glEbo_=" << glEbo_ << std::endl;
}

void BufferGeometry::render() {
  glBindVertexArray(glVao_);  // Is this even needed?
  constexpr int kStrideComponentCount = 5;
  glDrawArrays(GL_TRIANGLES, 0,
               (GLsizei)vertices_.size() / kStrideComponentCount);
  //  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}

auto operator<<(std::ostream &out, const BufferGeometry &geometry)
    -> std::ostream & {
  out << "verts=" << geometry.getVertices().size();
  return out;
}

}  // namespace app
