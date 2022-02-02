#ifndef APP_BLOCKMAP_H
#define APP_BLOCKMAP_H

class Block;

namespace app {

class BlockMap {
 public:
  auto get_block(int id) -> Block;
};

}  // namespace app

#endif  // APP_BLOCKMAP_H
