#include "Scene.h"

namespace BlockWorld {

void Scene::add(std::shared_ptr<Mesh> node) {
  _nodes.emplace_back(std::move(node));
}

}  // namespace BlockWorld