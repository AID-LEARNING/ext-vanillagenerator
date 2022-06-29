#include <lib/objects/constants/BlockList.h>
#include "NetherOrePopulator.h"

NetherOrePopulator::NetherOrePopulator(int_fast32_t worldHeight) {
  AddOre(OreType{NETHER_QUARTZ_ORE, 10, worldHeight - (10 * (worldHeight >> 7)), 13, 16, static_cast<int>(NETHERRACK.GetId())});
  AddOre(OreType{MAGMA, 26, 32 + (5 * (worldHeight >> 7)), 32, 16, static_cast<int>(NETHERRACK.GetId())});
  AddOre(OreType{GOLD_ORE_NETHER, 10, worldHeight - (10 * (worldHeight >> 7)), 5, 5, static_cast<int>(NETHERRACK.GetId())});
  AddOre(OreType{ANCIENT_DEBRIS, 10, worldHeight - (10 * (worldHeight >> 7)), 2, 8, static_cast<int>(NETHERRACK.GetId())});

}