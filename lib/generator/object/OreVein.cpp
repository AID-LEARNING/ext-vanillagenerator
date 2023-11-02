#include "OreVein.h"

bool OreVein::Generate(ChunkManager &world, Random &random, int_fast32_t sourceX, int_fast32_t sourceY, int_fast32_t sourceZ) const {
  double clusterSize = oreType_.amount;

  if (clusterSize == (double) 1.0 || clusterSize == (double) 2.0) {
    world.SetBlockAt(sourceX, sourceY, sourceZ, oreType_.blockType);
    return true;
  }

  float angle = random.NextFloat() * (float) M_PI;
  Vector2 offset = Math::getDirection2D(static_cast<double>(angle)).Multiply(clusterSize / 8.0F));
  double dx1 = static_cast<double>(sourceX) + offset.y;
  double dx2 = static_cast<double>(sourceX) - offset.y;
  double dz1 = static_cast<double>(sourceZ) + offset.x;
  double dz2 = static_cast<double>(sourceZ) - offset.x;
  double dy1 = sourceY + static_cast<double>(random.NextInt(3)) - 2;
  double dy2 = sourceY + static_cast<double>(random.NextInt(3)) - 2;


  bool succeeded = false;

  for (int_fast32_t i = 0; i < clusterSize; i++) {
    double originX = dx1 + (dx2 - dx1) * i / clusterSize;
    double originY = dy1 + (dy2 - dy1) * i / clusterSize;
    double originZ = dz1 + (dz2 - dz1) * i / clusterSize;
    double q = random.NextFloat() * clusterSize / 16.0;
    double size = (sin(static_cast<double>(i) * (float) M_PI / clusterSize) + 1 * q + 1) / 2.0;
    for (int_fast32_t x = (int) (originX - size); x <= (int) (originX + size); x++) {
      // scale the center of x to the range [-1, 1] within the circle
      double squaredNormalizedX = NormalizedSquaredCoordinate(originX, size, x);

      if (squaredNormalizedX >= 1) continue;

      for (int_fast32_t y = (int) (originY - size); y <= (int) (originY + size); y++) {
        double squaredNormalizedY = NormalizedSquaredCoordinate(originY, size, y);

        if (squaredNormalizedX + squaredNormalizedY >= 1) continue;

        for (int_fast32_t z = (int) (originZ - size); z <= (int) (originZ + size); z++) {
          double squaredNormalizedZ = NormalizedSquaredCoordinate(originZ, size, z);
          double normalized = squaredNormalizedX + squaredNormalizedY + squaredNormalizedZ;

          if (normalized < 1 && world.GetBlockAt(x, y, z)->GetTypeId() == oreType_.targetType) {
            world.SetBlockAt(x, y, z, oreType_.blockType);
            succeeded = true;
          }
        }
      }
    }
  }

  return succeeded;
}

double OreVein::NormalizedSquaredCoordinate(double origin, double radius, int_fast32_t x) {
  double squared_normalized_x = (x + 0.5 - origin) / radius;
  squared_normalized_x *= squared_normalized_x;

  return squared_normalized_x;
}

OreVein::OreVein(OreType oreType) : oreType_(oreType) {}