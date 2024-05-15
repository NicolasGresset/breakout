#include "utils/direction.h"
#include "utils/constants.h"
#include "utils/utils.h"
#include "utils/vector2D.h"

Direction::Direction() : Vector2D() {}

Direction::Direction(double x, double y) : Vector2D(x, y) {}

Direction::Direction(bool is_valid) : Vector2D(), is_valid_(is_valid) {}

Vector2D Direction::getVector() const {
  double norm = sqrt(pow(x_, 2) + pow(y_, 2));
  Vector2D result(x_ / norm, y_ / norm);

  // check if result is a unit vector
  ASSERT_FN(abs(result.getNorm() - 1) < EPSILON, [&]() {
    std::cerr << "Vector should be unit but as norm : " << result.getNorm()
              << std::endl;
  });
  return result;
}