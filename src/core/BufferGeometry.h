#ifndef BLOCK_WORLD_BUFFERGEOMETRY_H
#define BLOCK_WORLD_BUFFERGEOMETRY_H

#include <vector>

#include "../core.h"
namespace BlockWorld {

class BufferGeometry {
 public:
  BufferGeometry() noexcept { std::cout << "BufferGeometry" << std::endl; };
  explicit BufferGeometry(std::vector<float> vertices) noexcept;
  [[nodiscard]] auto getVertices() const -> const std::vector<float>& {
    return _vertices;
  };
  void render();

  // Copy: not supported
  ~BufferGeometry();
  BufferGeometry(const BufferGeometry& other) = delete;  // copy constructor
  auto operator=(const BufferGeometry& other) = delete;  // copy assignment
  // Move
  BufferGeometry(BufferGeometry&& other) noexcept
      : _vertices(
            std::exchange(other._vertices, std::vector<float>{})){};  // move
  auto operator=(BufferGeometry&& other) noexcept -> BufferGeometry& {
    std::swap(_vertices, other._vertices);
    return *this;
  }

 private:
  std::vector<float> _vertices{};
  GLuint VAO{0};
  GLuint VBO{0};
  GLuint EBO{0};
};

auto operator<<(std::ostream& out, const BufferGeometry& geometry)
    -> std::ostream&;

}  // namespace BlockWorld
#endif  // BLOCK_WORLD_BUFFERGEOMETRY_H
