#include <cmath>


Vector2 Vector2::Subtract(double ix, double iy) const {
  return Add(-ix, -iy);
}

Vector2 Vector2::SubtractVector(Vector2 from) const {
  return Add(-from.x, -from.y);
}

Vector2 Vector2::Add(double ix, double iy) const {
  return Vector2(x + ix, y + iy);
}
Vector2 Vector2::Multiply(double number) const {
    return Vector2(x * number, y * number);
}

Vector2 Vector2::Divide(double number) const {
    return Vector2(x / number, y / number);
}

Vector2 Vector2::AddVector(Vector2 from) const {
  return Add(from.x, from.y);
}

int_fast32_t Vector2::GetFloorX() const {
  return (int) std::floor(x);
}

int_fast32_t Vector2::GetFloorY() const {
  return (int) std::floor(y);
}