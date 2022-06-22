#include <math.h>

class Vector3f {
public:
  float x;
  float y;
  float z;

  Vector3f(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  Vector3f operator+(Vector3f other) {
    return {x + other.x, y + other.y, z + other.z};
  }

  Vector3f operator-(Vector3f other) {
    return {x - other.x, y - other.y, z - other.z};
  }

  Vector3f operator*(float scalar) {
    return {x * scalar, y * scalar, z * scalar};
  }

  Vector3f operator/(float scalar) {
    return {x / scalar, y / scalar, z / scalar};
  }

  Vector3f operator*(Vector3f other) {
    return {x * other.x, y * other.y, z * other.z};
  }

  Vector3f operator/(Vector3f other) {
    return {x / other.x, y / other.y, z / other.z};
  }

  void normalize() {
    float magnitude = this->magnitude();
    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
  }

  float magnitude() {
    return sqrt(x * x + y * y + z * z);
  }

  float dot(Vector3f other) {
    return x * other.x + y * other.y + z * other.z;
  }

  friend std::ostream& operator << (std::ostream& os, const Vector3f& v) {
    os << "Vector3f" << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
  }
};