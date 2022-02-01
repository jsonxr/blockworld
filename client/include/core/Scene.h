#ifndef APP_SCENE_H
#define APP_SCENE_H

#include "../core.h"
#include "Mesh.h"

namespace app {

class Scene {
 public:
  Scene() = default;
  void add(std::shared_ptr<Mesh> mesh);
  [[nodiscard]] auto getNodes() const
      -> const std::vector<std::shared_ptr<Mesh>> & {
    return nodes_;
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
  std::vector<std::shared_ptr<Mesh>> nodes_;
};

}  // namespace app

#endif  // APP_SCENE_H
