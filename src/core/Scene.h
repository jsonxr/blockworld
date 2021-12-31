#ifndef BLOCKWORLD_SCENE_H
#define BLOCKWORLD_SCENE_H

#include "../core.h"
#include "Mesh.h"

namespace BlockWorld {

class Scene {
 public:
  Scene() = default;
  void add(std::shared_ptr<Mesh> mesh);
  [[nodiscard]] auto getNodes() const
      -> const std::vector<std::shared_ptr<Mesh>>& {
    return _nodes;
  }
  // auto getMeshes2() -> const std::vector<Mesh>& { return _meshes; }

  //  // Copy: not supported
  //  Scene(const Scene& other) = default;                     // copy
  //  constructor auto operator=(const Scene& other) -> Scene& = default;  //
  //  copy assignment
  //  // Move
  //  Scene(Scene&& other) noexcept = default;
  //  auto operator=(Scene&& other) noexcept -> Scene& = default;

 private:
  std::vector<std::shared_ptr<Mesh>> _nodes;
};

}  // namespace BlockWorld

#endif  // BLOCKWORLD_SCENE_H
