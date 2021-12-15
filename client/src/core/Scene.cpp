#include "core/Scene.h"

namespace block_world {

void Scene::add(std::shared_ptr<Mesh> mesh) {
  nodes_.emplace_back(std::move(mesh));
}

}  // namespace block_world