#include <math.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "Vector3f.hpp"

#define WIDTH 30
#define HEIGHT 30

float t = 0.0f;

static char stage[HEIGHT * WIDTH];

const std::string clear_sequence = "\e[1;1H\e[2J";
const std::string shades = " .:-=+*#%@";

float sdf(Vector3f p) {
  struct Vector3f center = {0.0f, 0.0f, 0.0f};
  return (p - center).magnitude() - 0.5;
}

char get_shade(Vector3f pos) {
  Vector3f L = {
    1.0f + cos(t),
    1.0f,
    1.0f + sin(t)
  };

  L.normalize();

  float dt = 1e-6;
  float curr = sdf(pos);

  Vector3f x = {pos.x + dt, pos.y, pos.z};
  float dx = sdf(x) - curr;

  Vector3f y = {pos.x, pos.y + dt, pos.z};
  float dy = sdf(y) - curr;

  Vector3f z = {pos.x, pos.y, pos.z + dt};
  float dz = sdf(z) - curr;

  Vector3f N = {0, 0, 0};
  N.x = (dx - pos.x) / dt;
  N.y = (dy - pos.y) / dt;
  N.z = (dz - pos.z) / dt;

  if (N.magnitude() < 1e-9) {
    return shades[0];
  }

  N.normalize();

  float diffuse = L.dot(N);
  diffuse = (diffuse + 1.0) / 2.0 * shades.length();
  return shades[(int) floor(diffuse) % shades.length()];
}

void raymarch() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      Vector3f position = {0.0, 0.0, -10.0};
      Vector3f target = {
        (float) x / (float) WIDTH - 0.5f,
        (float) y / (float) HEIGHT - 0.5f,
        -1.5f,
      };

      Vector3f ray = target - position;
      ray.normalize();

      float dist;
      float max_dist = 10000.0f;
      char shade = shades[0];

      for (int i = 0; i < 10000; i++) {
        if (fabs(position.x) > max_dist ||
            fabs(position.y) > max_dist ||
            fabs(position.z) > max_dist) {
          break;
        }

        dist = sdf(position);
        if (dist < 1e-6) {
          shade = get_shade(position);
          break;
        }

        position = position + ray * dist;
      }

      stage[y * WIDTH + x] = shade;
    }
  }
}

void clear() {
  std::cout << clear_sequence;
}

void render() {
  clear();
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      std::cout << stage[y * WIDTH + x] << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  while(true) {
    raymarch();
    render();
    t += 0.01666667f;
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }

  return 0;
}
