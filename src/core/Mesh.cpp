//
// Created by Jason Rowland on 12/17/21.
//

#include "Mesh.h"

#include <cmath>

namespace BlockWorld {

Mesh::Mesh(std::unique_ptr<BufferGeometry> bufferGeometry,
           std::unique_ptr<Material> material)
    : _bufferGeometry(std::move(bufferGeometry)),
      _material(std::move(material)) {
  std::cout << "Mesh(b,m) " << _bufferGeometry->getVertices().size()
            << std::endl;
}

void Mesh::compile() {
  if (VAO != 0) {
    // Already compiled, just ignore this
    return;
  }

  // TODO: Figure out how to be certain we only have max int values
  const auto vertices = _bufferGeometry->getVertices();
  const auto indices = _bufferGeometry->getIndices();
  GLsizei vertexSize = _bufferGeometry->getVertices().size() * sizeof(float);
  GLsizei indicesSize = _bufferGeometry->getIndices().size() * sizeof(u32);

  if (vertexSize < 0 || indicesSize < 0) {
    std::cerr << "Nothing in the mesh to compile. skipping..." << std::endl;
    return;
  }

  _material->getProgram().use();

  if (_material->getProgram().use()) {
    // Create Buffers
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(NULL);

    std::cerr << "Compile mesh VAO=" << VAO << " VBO=" << VBO << " EBO=" << EBO
              << std::endl;
  } else {
    std::cerr << "Mesh can't compile" << std::endl;
  };
}

void Mesh::render() const {
  if (_material->getProgram().use() && VAO != 0) {
    double timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0F) + 0.5F;
    _material->getProgram().setUniform("ourColor",
                                       vec4{0.F, greenValue, 0.F, 1.0F});

    GLsizei indexCount = _bufferGeometry->getIndices().size();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
  } else {
    std::cerr << "Cant render " << std::endl;
  }
}

auto operator<<(std::ostream& out, Mesh mesh) -> std::ostream& {
  const BufferGeometry* geometry = mesh.getBufferGeometry();
  out << "Mesh: ";
  return out;
}

}  // namespace BlockWorld
