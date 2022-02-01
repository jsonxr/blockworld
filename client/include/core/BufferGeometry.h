#ifndef APP_BUFFER_GEOMETRY_H
#define APP_BUFFER_GEOMETRY_H

#include <vector>

#include "../core.h"
namespace app {

struct BufferAttribute {
  GLenum type{GL_FLOAT};
  short count{};
};

class BufferGeometry {
 public:
  explicit BufferGeometry(const std::vector<GLfloat> &vertices,
                          const std::vector<BufferAttribute> &attributes);
  ~BufferGeometry() noexcept;
  BufferGeometry(const BufferGeometry &other) = delete;
  auto operator=(const BufferGeometry &other) = delete;
  BufferGeometry(BufferGeometry &&other) noexcept;
  auto operator=(BufferGeometry &&other) noexcept -> BufferGeometry &;

  void render() const;

  GLuint glVao_{0};
  GLuint glVbo_{0};
  GLsizei count_{0};
  // GLsizei size_{0};
  // int stride_{0};
};

// class BufferGeometry {
//  public:
//   BufferGeometry() noexcept { std::cout << "BufferGeometry" << std::endl; };
//   explicit BufferGeometry(std::vector<float> vertices) noexcept;
//   [[nodiscard]] auto getVertices() const -> const std::vector<float> & {
//     return vertices_;
//   };
//   void render();

//   // Copy: not supported
//   ~BufferGeometry();
//   BufferGeometry(const BufferGeometry &other) = delete;  // copy constructor
//   auto operator=(const BufferGeometry &other) = delete;  // copy assignment
//   // Move
//   BufferGeometry(BufferGeometry &&other) noexcept
//       : vertices_(
//             std::exchange(other.vertices_, std::vector<float>{})){};  // move
//   auto operator=(BufferGeometry &&other) noexcept -> BufferGeometry & {
//     std::swap(vertices_, other.vertices_);
//     return *this;
//   }

//  private:
//   std::vector<float> vertices_{};
//   GLuint glVao_{0};
//   GLuint glVbo_{0};
//   GLuint glEbo_{0};
// };

// auto operator<<(std::ostream &out, const BufferGeometry &geometry)
//     -> std::ostream &;

}  // namespace app
#endif  // APP_BUFFER_GEOMETRY_H
