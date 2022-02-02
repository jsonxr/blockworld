#ifndef APP_CORE_BLOCKMATERIAL_H
#define APP_CORE_BLOCKMATERIAL_H

#include "webgl/WebGLProgram.h"

namespace app {

class BlockMaterial {
 public:
  BlockMaterial() = default;

 private:
  WebGLProgram program_{};
};

}  // namespace app

#endif  // APP_CORE_BLOCKMATERIAL_H
