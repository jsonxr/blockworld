//
// Created by Jason Rowland on 12/15/21.
//

#ifndef BLOCKWORLD_SCENE_H
#define BLOCKWORLD_SCENE_H
#include "../core.h"
#include "Mesh.h"

namespace BlockWorld {

class Scene {
 public:
  Scene() { std::cout << "Scene" << std::endl; };
  ~Scene() { std::cout << "~Scene" << std::endl; };

  void add(std::unique_ptr<Mesh> mesh);
  [[nodiscard]] auto getMeshes() const
      -> const std::vector<std::unique_ptr<Mesh>>& {
    return _meshes;
  }
  // auto getMeshes2() -> const std::vector<Mesh>& { return _meshes; }

  // Copy: not supported
  //  Scene(const Scene& other) = delete;           // copy constructor
  //  auto operator=(const Scene& other) = delete;  // copy assignment
  //  // Move
  //  Scene(Scene&& other) noexcept
  //      : _meshes(std::exchange(other._meshes, std::vector<Mesh>{})){};
  //  auto operator=(Scene&& other) noexcept -> Scene& {
  //    std::swap(_meshes, other._meshes);
  //    return *this;
  //  }

 private:
  std::vector<std::unique_ptr<Mesh>> _meshes;
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_SCENE_H
