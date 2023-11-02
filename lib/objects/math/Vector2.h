#ifndef EXT_VANILLAGENERATOR_LIB_OBJECTS_RANDOM_VECTOR2_H_
#define EXT_VANILLAGENERATOR_LIB_OBJECTS_RANDOM_VECTOR2_H_

#include <cstdint>

class Vector2 {
 public:
  template<typename Y>
  explicit Vector2(Y ix, Y iy) : x(ix), y(iy){};


  [[nodiscard]] int_fast32_t GetFloorX() const;
  [[nodiscard]] int_fast32_t GetFloorY() const;

  [[nodiscard]] Vector2 Subtract(double ix, double iy) const;
  [[nodiscard]] Vector2 SubtractVector(Vector2 from) const;
  [[nodiscard]] Vector2 Add(double ix, double iy) const;
  [[nodiscard]] Vector2 AddVector(Vector2 from) const;
  [[nodiscard]] Vector2 Multiply(double number) const;
  [[nodiscard]] Vector2 Divide(double number) const;


  double x;
  double y;
};

#endif // EXT_VANILLAGENERATOR_LIB_OBJECTS_RANDOM_VECTOR3_H_
