//
// Created by Jason Rowland on 12/17/21.
//

#ifndef BLOCKWORLD_MESH_H
#define BLOCKWORLD_MESH_H

#include "BufferGeometry.h"
#include "Material.h"

namespace BlockWorld {

class Mesh {
 public:
  Mesh() { std::cout << "Mesh" << std::endl; };
  Mesh(std::unique_ptr<BufferGeometry> bufferGeometry,
       std::unique_ptr<Material> material);
  void compile();
  void render() const;

  [[nodiscard]] auto getBufferGeometry() const -> const BufferGeometry* {
    return _bufferGeometry.get();
  };
  [[nodiscard]] auto getMaterial() const -> const Material* {
    return _material.get();
  };

 private:
  std::unique_ptr<BufferGeometry> _bufferGeometry;
  std::unique_ptr<Material> _material;

  GLuint VAO{};
  GLuint VBO{};
  GLuint EBO{};
};

auto operator<<(std::ostream& out, Mesh mesh) -> std::ostream&;

}  // namespace BlockWorld
#endif  // BLOCKWORLD_MESH_H
