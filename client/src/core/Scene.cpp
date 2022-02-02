#include "Scene.h"

namespace app {

void Scene::add(std::shared_ptr<Mesh> mesh) {
  nodes_.emplace_back(std::move(mesh));
}

}  // namespace app