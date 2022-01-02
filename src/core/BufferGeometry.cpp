#include "BufferGeometry.h"

#include <bit>
#include <iostream>
#include <vector>

namespace BlockWorld {

BufferGeometry::~BufferGeometry() {
  std::cout << "~BufferGeometry"
            << " VAO=" << VAO << " VBO=" << VBO << " EBO=" << EBO << std::endl;
  if (VAO > 0) {
    glDeleteVertexArrays(1, &VAO);
    VAO = 0;
  }
  if (VBO > 0) {
    glDeleteBuffers(1, &VBO);
    VBO = 0;
  }
  if (EBO > 0) {
    glDeleteBuffers(1, &EBO);
    EBO = 0;
  }
}

// BufferGeometry::BufferGeometry(std::vector<GLfloat> vertices) noexcept
//     : _vertices(std::move(vertices)) {
//   std::cout << "BufferGeometry size=" << _vertices.size() << std::endl;
//
//   // TODO: Figure out how to be certain we only have max int values
//   GLsizei vertexSize = _vertices.size() * sizeof(GLfloat);
//
//   if (vertexSize < 0) {
//     std::cerr << "Nothing in the mesh to compile. skipping..." << std::endl;
//     return;
//   }
//
//   // Create Buffers
//
//   glGenVertexArrays(1, &VAO);
//   glBindVertexArray(VAO);
//
//   glGenBuffers(1, &VBO);
//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferData(GL_ARRAY_BUFFER, vertexSize, _vertices.data(),
//   GL_STATIC_DRAW);
//
//   constexpr int STRIDE = 5 * sizeof(GLfloat);
//   auto* offsetPosition = (void*)nullptr;
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE, offsetPosition);
//   glEnableVertexAttribArray(0);
//   //  auto* offsetColor = (void*)(3 * sizeof(GLfloat));
//   //  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE, offsetColor);
//   //  glEnableVertexAttribArray(1);
//
//   auto* offsetTexture = (void*)(3 * sizeof(GLfloat));
//   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE, offsetTexture);
//   glEnableVertexAttribArray(1);
//
//   std::cout << "Compiled mesh VAO=" << VAO << " VBO=" << VBO << " EBO=" <<
//   EBO
//             << std::endl;
// }

BufferGeometry::BufferGeometry(std::vector<GLfloat> vertices) noexcept
    : _vertices(std::move(vertices)) {
  std::cout << "BufferGeometry size=" << _vertices.size() << std::endl;

  // TODO: Figure out how to be certain we only have max int values
  // size_t vertexSize = _vertices.size() * sizeof(GLfloat);
  size_t vertexSize = _vertices.size() * sizeof(GLfloat);

  if (vertexSize < 0) {
    std::cerr << "Nothing in the mesh to compile. skipping..." << std::endl;
    return;
  }

  // Create Buffers
#ifndef __EMSCRIPTEN__
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
#else

#endif



  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertexSize, _vertices.data(), GL_STATIC_DRAW);

  //  glGenBuffers(1, &EBO);
  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, _indices.data(),
  //               GL_STATIC_DRAW);

  constexpr int STRIDE = 5 * sizeof(GLfloat);
  constexpr GLint LOC_APOS = 0;
  constexpr GLint LOC_TEXTURE = 1;
  constexpr int POSITION_FLOATS = 3;
  constexpr int TEXTURE_FLOATS = 2;
  glEnableVertexAttribArray(LOC_APOS);     // aPos location
  glEnableVertexAttribArray(LOC_TEXTURE);  // aTexCoord location
  glVertexAttribPointer(LOC_APOS, POSITION_FLOATS, GL_FLOAT, GL_FALSE, STRIDE,
                        (const GLvoid*)nullptr);

  const auto* offsetTexture =
      (const GLvoid*)(POSITION_FLOATS * sizeof(GLfloat));
  glVertexAttribPointer(LOC_TEXTURE, TEXTURE_FLOATS, GL_FLOAT, GL_FALSE, STRIDE,
                        offsetTexture);

  glBindVertexArray(NULL);
  std::cout << "Compiled mesh VAO=" << VAO << " VBO=" << VBO << " EBO=" << EBO
            << std::endl;
}

void BufferGeometry::render() {
  glBindVertexArray(VAO);  // Is this even needed?
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)_vertices.size());
  //  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}

auto operator<<(std::ostream& out, const BufferGeometry& geometry)
    -> std::ostream& {
  out << "verts=" << geometry.getVertices().size();
  return out;
}

}  // namespace BlockWorld
