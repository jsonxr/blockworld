#ifndef APP_BUFFER_GEOMETRY_H
#define APP_BUFFER_GEOMETRY_H

#include <vector>

#include "../core.h"
namespace app {

struct BufferAttribute {
  GLenum type{GL_FLOAT};
  short count{};
};

struct BufferGeometry {
  std::vector<BufferAttribute> attributes{};
  std::vector<GLfloat> vertices{};
  std::vector<int> elements{};

  void append(const BufferGeometry &v);
};

class BufferGeometryGfx {
 public:
  explicit BufferGeometryGfx(const BufferGeometry &geometry);
  ~BufferGeometryGfx() noexcept;
  BufferGeometryGfx(const BufferGeometryGfx &other) = delete;
  auto operator=(const BufferGeometryGfx &other) = delete;
  BufferGeometryGfx(BufferGeometryGfx &&other) noexcept;
  auto operator=(BufferGeometryGfx &&other) noexcept -> BufferGeometryGfx &;

  void render() const;

 private:
  GLuint glVao_{0};
  GLuint glVbo_{0};
  GLuint glEbo_{0};
  GLsizei count_{0};
  GLsizei elements_size_{0};
};

}  // namespace app

#endif  // APP_BUFFER_GEOMETRY_H
