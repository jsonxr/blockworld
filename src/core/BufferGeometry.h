#ifndef BLOCKWORLD_BUFFERGEOMETRY_H
#define BLOCKWORLD_BUFFERGEOMETRY_H

#include <vector>

#include "../core.h"
namespace BlockWorld {

class BufferGeometry {
 public:
  BufferGeometry() noexcept { std::cout << "BufferGeometry" << std::endl; };
  BufferGeometry(std::vector<GLfloat> vertices,
                 std::vector<u32> indices) noexcept;
  [[nodiscard]] auto getVertices() const -> const std::vector<float>& {
    return _vertices;
  };
  [[nodiscard]] auto getIndices() const -> const std::vector<u32>& {
    return _indices;
  };
  void render();

  // Copy: not supported
  ~BufferGeometry();
  BufferGeometry(const BufferGeometry& other) = delete;  // copy constructor
  auto operator=(const BufferGeometry& other) = delete;  // copy assignment
  // Move
  BufferGeometry(BufferGeometry&& other) noexcept
      : _indices(std::exchange(other._indices, std::vector<u32>{})),
        _vertices(
            std::exchange(other._vertices, std::vector<GLfloat>{})){};  // move
  auto operator=(BufferGeometry&& other) noexcept -> BufferGeometry& {
    std::swap(_vertices, other._vertices);
    std::swap(_indices, other._indices);
    return *this;
  }

 private:
  std::vector<GLfloat> _vertices{};
  std::vector<u32> _indices{};
  GLuint VAO{0};
  GLuint VBO{0};
  GLuint EBO{0};
};

auto operator<<(std::ostream& out, const BufferGeometry& geometry)
    -> std::ostream&;

}  // namespace BlockWorld
#endif  // BLOCKWORLD_BUFFERGEOMETRY_H
