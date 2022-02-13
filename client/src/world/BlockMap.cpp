//
// Created by Jason Rowland on 2/3/22.
//

#include "BlockMap.h"

#include "utils/memory.h"

namespace app {

BlockMap::BlockMap() {
  // TODO: Load these from a resource instead
  Block air{};
  air.is_transparent = true;
  air.type = BlockType::kNull;
  air.name = "minecraft:block/air";
  add_block(std::move(air));

  Block bedrock{};
  bedrock.name = "minecraft:block/bedrock";
  bedrock.xp = Face{.texture = "minecraft:block/bedrock"};
  bedrock.xn = Face{.texture = "minecraft:block/bedrock"};
  bedrock.yp = Face{.texture = "minecraft:block/bedrock"};
  bedrock.yn = Face{.texture = "minecraft:block/bedrock"};
  bedrock.zp = Face{.texture = "minecraft:block/bedrock"};
  bedrock.zn = Face{.texture = "minecraft:block/bedrock"};
  add_block(std::move(bedrock));

  Block dirt{};
  dirt.name = "minecraft:block/dirt";
  dirt.xp = Face{.texture = "minecraft:block/dirt"};
  dirt.xn = Face{.texture = "minecraft:block/dirt"};
  dirt.yp = Face{.texture = "minecraft:block/dirt"};
  dirt.yn = Face{.texture = "minecraft:block/dirt"};
  dirt.zp = Face{.texture = "minecraft:block/dirt"};
  dirt.zn = Face{.texture = "minecraft:block/dirt"};
  add_block(std::move(dirt));

  Block grass{};
  grass.name = "minecraft:block/grass_block";
  grass.xp = Face{.texture = "minecraft:block/grass_block_side"};
  grass.xn = Face{.texture = "minecraft:block/grass_block_side"};
  grass.yp = Face{.texture = "minecraft:block/azalea_top"};
  grass.yn = Face{.texture = "minecraft:block/dirt"};
  grass.zp = Face{.texture = "minecraft:block/grass_block_side"};
  grass.zn = Face{.texture = "minecraft:block/grass_block_side"};
  add_block(grass);

  Block stone{};
  stone.name = "minecraft:block/stone";
  stone.xn = Face{.texture = "minecraft:block/stone"};
  stone.xp = Face{.texture = "minecraft:block/stone"};
  stone.yp = Face{.texture = "minecraft:block/stone"};
  stone.yn = Face{.texture = "minecraft:block/stone"};
  stone.zp = Face{.texture = "minecraft:block/stone"};
  stone.zn = Face{.texture = "minecraft:block/stone"};
  add_block(stone);

  Block birch_wood{};
  birch_wood.name = "minecraft:block/birch_planks";
  birch_wood.xn = Face{.texture = "minecraft:block/birch_planks"};
  birch_wood.xp = Face{.texture = "minecraft:block/birch_planks"};
  birch_wood.yp = Face{.texture = "minecraft:block/birch_planks"};
  birch_wood.yn = Face{.texture = "minecraft:block/birch_planks"};
  birch_wood.zp = Face{.texture = "minecraft:block/birch_planks"};
  birch_wood.zn = Face{.texture = "minecraft:block/birch_planks"};
  add_block(birch_wood);
}

void BlockMap::add_block(Block block) {
  auto index = blocks_.size();
  auto name = block.name;
  blocks_.emplace_back(std::move(block));
  by_name_.emplace(name, index);
}

auto BlockMap::get_block(int16 id) const noexcept -> const Block * {
  if (id < 0 || id >= blocks_.size()) {
    return nullptr;
  }
  const auto *block = &blocks_.at(id);
  return block;
}

auto BlockMap::get_block_id(const std::string &name) const noexcept -> int16 {
  by_name_.contains(name);
  if (by_name_.contains(name)) {
    auto id = by_name_.at(name);
    return id;
  }

  return 0;
}

}  // namespace app