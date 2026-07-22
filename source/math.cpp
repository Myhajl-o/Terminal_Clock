#include "math.hpp"
#include "Coordinates.hpp"
#include <cmath>
#include <vector>

const float convert = 180.0f / M_PI;

void Coordinate_center(Coordinates &center, const int &size_x,
                       const int &size_y) {
  center.x = size_x / 2;
  center.y = size_y / 2;
}

void Radius(int &radius, const int &size_x, const int &size_y) {
  if (size_x < (size_y * 2)) {
    radius = (size_x / 4) - 1;
  } else {
    radius = (size_y / 2) - 1;
  }
}

void Coordinates_circle(const int &radius, std::vector<Coordinates> &circle) {
  int d = 3 - 2 * radius;
  int i = 0;
  int temp_x = 0, temp_y = radius;
  circle.push_back(Coordinates{temp_x, temp_y});

  do {
    if (d < 0) {
      d = d + 4 * circle[i].x + 6;
      temp_x++;
      circle.push_back(Coordinates{temp_x, temp_y});

    } else if (d >= 0) {
      d = d + 4 * (circle[i].x - circle[i].y) + 10;
      temp_x++;
      temp_y--;
      circle.push_back(Coordinates{temp_x, temp_y});
    }
    i++;
  } while ((circle[i].x == circle[i].y || circle[i].x < circle[i].y));

  circle.resize(i * 2);
  for (int j = i * 2 - 1; j >= i; j--) {
    circle[j].x = circle[(i * 2 - 1) - j].y;
    circle[j].y = circle[(i * 2 - 1) - j].x;
  }
}

void Coordinate_upgrade(std::vector<Coordinates> &circle) {
  std::vector<Coordinates> temp = circle;
  circle.resize(circle.size() * 2 - 1);
  int j = 0;
  int add;

  for (size_t i = 0; i < circle.size(); i += 2) {
    add = temp[j].x < temp[j + 1].x;

    circle[i].x = temp[j].x * 2;
    circle[i].y = temp[j].y;

    circle[i + 1].x = temp[j].x * 2 + add;
    circle[i + 1].y = temp[j].y;
    j++;
  }
}

void Comparison(int degree, Coordinates &tick_element,
                const std::vector<Coordinates> &circle) {
  float difference[2];
  difference[0] =
      std::abs(degree - (convert * std::atan2((float)circle[1].x,
                                              (float)circle[1].y * 2)));

  for (size_t i = 2; i < circle.size(); i++) {
    difference[1] =
        std::abs(degree - (convert * std::atan2((float)circle[i].x,
                                                (float)circle[i].y * 2)));

    if (difference[0] < difference[1]) {
      tick_element.x = circle[i - 1].x;
      tick_element.y = circle[i - 1].y;

      return;
    }
    difference[0] = difference[1];
  }
}

void Calculation_degrees(Coordinates (&tick)[14],
                         const std::vector<Coordinates> &circle) {

  for (int i = 0; i < 14; i++) {
    Comparison((i + 1) * 6, tick[i], circle);
  }
}
