#include <lib/objects/constants/BlockList.h>
#include "NetherOrePopulator.h"

NetherOrePopulator::NetherOrePopulator(int_fast32_t worldHeight) {
  AddOre(OreType{NETHER_QUARTZ_ORE, 10, worldHeight - (10 * (worldHeight >> 7)), 13, static_cast<int>(NETHERRACK.GetId()), 16});
  AddOre(OreType{MAGMA, 26, 32 + (5 * (worldHeight >> 7)), 32, static_cast<int>(NETHERRACK.GetId()), 16});
  AddOre(OreType{GOLD_ORE_NETHER, 10, worldHeight - (10 * (worldHeight >> 7)), 5, static_cast<int>(NETHERRACK.GetId()), 8});
  AddOre(OreType{ANCIENT_DEBRIS, 10, worldHeight - (10 * (worldHeight >> 7)), 2, static_cast<int>(NETHERRACK.GetId())});

}