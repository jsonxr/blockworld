#ifndef APP_BUFFER_GEOMETRY_H
#define APP_BUFFER_GEOMETRY_H

#include <vector>

#include "../core.h"
namespace app {

class BufferGeometry {
 public:
  BufferGeometry() noexcept { std::cout << "BufferGeometry" << std::endl; };
  explicit BufferGeometry(std::vector<float> vertices) noexcept;
  [[nodiscard]] auto getVertices() const -> const std::vector<float> & {
    return vertices_;
  };
  void render();

  // Copy: not supported
  ~BufferGeometry();
  BufferGeometry(const BufferGeometry &other) = delete;  // copy constructor
  auto operator=(const BufferGeometry &other) = delete;  // copy assignment
  // Move
  BufferGeometry(BufferGeometry &&other) noexcept
      : vertices_(
            std::exchange(other.vertices_, std::vector<float>{})){};  // move
  auto operator=(BufferGeometry &&other) noexcept -> BufferGeometry & {
    std::swap(vertices_, other.vertices_);
    return *this;
  }

 private:
  std::vector<float> vertices_{};
  GLuint glVao_{0};
  GLuint glVbo_{0};
  GLuint glEbo_{0};
};

auto operator<<(std::ostream &out, const BufferGeometry &geometry)
    -> std::ostream &;

}  // namespace app
#endif  // APP_BUFFER_GEOMETRY_H
