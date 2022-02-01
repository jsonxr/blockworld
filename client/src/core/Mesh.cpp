#include "core/Mesh.h"

#include <array>
#include <cmath>

namespace app {

constexpr float kThird = 0.3F;
constexpr float kHalf = 0.5F;

constexpr float kAngleIncrement = 30.0F;
constexpr std::array<vec3, 10> kCubePositions{
    vec3(0.0F, 0.0F, 0.0F),    vec3(2.0F, 5.0F, -15.0F),
    vec3(-1.5F, -2.2F, -2.5F), vec3(-3.8F, -2.0F, -12.3F),
    vec3(2.4F, -0.4F, -3.5F),  vec3(-1.7F, 3.0F, -7.5F),
    vec3(1.3F, -2.0F, -2.5F),  vec3(1.5F, 2.0F, -2.5F),
    vec3(1.5F, 0.2F, -1.5F),   vec3(-1.3F, 1.0F, -1.5F)};

Mesh::Mesh(std::shared_ptr<BufferGeometry> bufferGeometry,
           std::shared_ptr<Material> material) noexcept
    : bufferGeometry_(std::move(bufferGeometry)),
      material_(std::move(material)) {}

void Mesh::render(Camera &camera) const {
  material_->render(camera);

  for (int i = 0; i < kCubePositions.size(); i++) {
    // calculate the model matrix for each object and pass it to shader before
    // drawing
    glm::mat4 model = glm::mat4(1.0F);
    model = glm::translate(model, kCubePositions.at(i));
    float angle = static_cast<float>(i) * kAngleIncrement;
    model = glm::rotate(model, glm::radians(angle), vec3(1.0F, kThird, kHalf));

    material_->setModelMatrix(model);
    bufferGeometry_->render();
  }
}

}  // namespace app
