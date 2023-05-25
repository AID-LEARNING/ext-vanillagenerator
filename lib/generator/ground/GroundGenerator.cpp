#include "GroundGenerator.h"

#include <lib/biomes/BiomeClimate.h>
#include <lib/objects/math/Math.h>

void GroundGenerator::GenerateTerrainColumn(ChunkManager &world,
                                            Random &random,
                                            int_fast32_t x,
                                            int_fast32_t z,
                                            int biome,
                                            double surfaceNoise) {

  int seaLevel = 64;

  auto topMat = topMaterial.GetStateId();
  auto groundMat = groundMaterial.GetStateId();
  int groundMatId = groundMaterial.GetId();

  int_fast32_t chunkX = x;
  int_fast32_t chunkZ = z;

  int surfaceHeight = Math::Max((int) (surfaceNoise / 3.0 + 3.0 + random.NextFloat() * 0.25), 1);
  int deep = -1;

  int air = AIR.GetStateId();
  int stone = STONE.GetStateId();
  int sandstone = SANDSTONE.GetStateId();
  int gravel = GRAVEL.GetStateId();
  int bedrock = BEDROCK.GetStateId();
  int ice = ICE.GetStateId();

  Chunk *chunk = world.GetChunk(x >> 4, z >> 4);
  auto blockX = static_cast<int_fast8_t>(x & 0x0f);
  auto blockZ = static_cast<int_fast8_t>(z & 0x0f);

  for (int_fast16_t y = 255; y >= 0; --y) {
    if (y <= random.NextInt(5)) {
      chunk->setBlockStateId(blockX, y, blockZ, bedrock);
    } else {
      int mat_id = MinecraftBlock(chunk->getBlockStateId(blockX, y, blockZ)).GetId();
      if (mat_id == AIR.GetId()) {
        deep = -1;
      } else if (mat_id == STONE.GetId()) {
        if (deep == -1) {
          if (y >= seaLevel - 5 && y <= seaLevel) {
            topMat = topMaterial.GetStateId();
            groundMat = groundMaterial.GetStateId();
            groundMatId = groundMaterial.GetId();
          }

          deep = surfaceHeight;
          if (y >= seaLevel - 2) {
            chunk->setBlockStateId(blockX, y, blockZ, topMat);
          } else if (y < seaLevel - 8 - surfaceHeight) {
            topMat = air;
            groundMat = stone;
            groundMatId = STONE.GetId();
            chunk->setBlockStateId(blockX, y, blockZ, gravel);
          } else {
            chunk->setBlockStateId(blockX, y, blockZ, groundMat);
          }
        } else if (deep > 0) {
          --deep;
          chunk->setBlockStateId(blockX, y, blockZ, groundMat);

          if (deep == 0 && groundMatId == SAND.GetId()) {
            deep = static_cast<int>(random.NextInt(4) + Math::Max(0, static_cast<int>(y - seaLevel - 1)));
            groundMat = sandstone;
            groundMatId = SANDSTONE.GetId();
          }
        }
      } else if (mat_id == STILL_WATER.GetId() && y == seaLevel - 2 && BiomeClimate::IsCold(biome, chunkX, y, chunkZ)) {
        chunk->setBlockStateId(blockX, y, blockZ, ice);
      }
    }
  }
}