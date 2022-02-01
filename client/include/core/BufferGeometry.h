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
};

}  // namespace app
#endif  // APP_BUFFER_GEOMETRY_H
