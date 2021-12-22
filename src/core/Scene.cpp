//
// Created by Jason Rowland on 12/15/21.
//

#include "Scene.h"

namespace BlockWorld {

void Scene::add(std::unique_ptr<Mesh> mesh) {
  _meshes.push_back(std::move(mesh));
}

}  // namespace BlockWorld