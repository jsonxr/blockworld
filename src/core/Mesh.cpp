#include "Mesh.h"

#include <cmath>
#include <glm/ext.hpp>
#include <regex>

namespace BlockWorld {

vec3 cubePositions[] = {vec3(0.0f, 0.0f, 0.0f),    vec3(2.0f, 5.0f, -15.0f),
                        vec3(-1.5f, -2.2f, -2.5f), vec3(-3.8f, -2.0f, -12.3f),
                        vec3(2.4f, -0.4f, -3.5f),  vec3(-1.7f, 3.0f, -7.5f),
                        vec3(1.3f, -2.0f, -2.5f),  vec3(1.5f, 2.0f, -2.5f),
                        vec3(1.5f, 0.2f, -1.5f),   vec3(-1.3f, 1.0f, -1.5f)};

Mesh::Mesh(std::shared_ptr<BufferGeometry> bufferGeometry,
           std::shared_ptr<Material> material) noexcept
    : _bufferGeometry(std::move(bufferGeometry)),
      _material(std::move(material)) {
  std::cout << "Mesh(b,m) verts=" << _bufferGeometry->getVertices().size()
            << std::endl;
}

void Mesh::render() const {
  _material->render();

  for (unsigned int i = 0; i < 10; i++) {
    // calculate the model matrix for each object and pass it to shader before
    // drawing
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i;
    model = glm::rotate(model, glm::radians(angle), vec3(1.0f, 0.3f, 0.5f));

    _material->setModelMatrix(model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  _bufferGeometry->render();
}

}  // namespace BlockWorld
