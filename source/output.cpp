#include "output.hpp"
#include "Coordinates.hpp"
#include "math.hpp"
#include <iostream>
#include <string>

#include <vector>

void clear() {
  std::cout << "\033[0m" << std::flush;
  system("clear");
}

void output_space(const int &x, const int &y, int color) {
  std::cout << "\033[" << color << "m\033[" << y << ";" << x << "H \033[47m"
            << std::flush;
}

void output_char(const int &x, const int &y, char c) {
  std::cout << "\033[30m\033[" << y << ";" << x << "H" << c << std::flush;
}

void background(const int &x, const int &y) {
  std::string canvas(x * y, ' ');
  std::cout << "\033[47m" << canvas;
}

void draw_circle(const Coordinates &center,
                 const std::vector<Coordinates> &circle) {
  for (std::size_t i = 0; i < circle.size(); i++) {
    output_space((center.x + circle[i].x * 2), (center.y - circle[i].y), 40);
    output_space((center.x + circle[i].x * 2) + 1, (center.y - circle[i].y),
                 40);
  }
  for (int i = circle.size() - 2; i >= 0; i--) {
    output_space((center.x + circle[i].x * 2), (center.y + circle[i].y), 40);
    output_space((center.x + circle[i].x * 2) + 1, (center.y + circle[i].y),
                 40);
  }
  for (std::size_t i = 0; i < circle.size(); i++) {
    output_space((center.x - circle[i].x * 2) - 2, (center.y + circle[i].y),
                 40);
    output_space((center.x - circle[i].x * 2) - 1, (center.y + circle[i].y),
                 40);
  }
  for (int i = circle.size() - 2; i >= 0; i--) {
    output_space((center.x - circle[i].x * 2) - 2, (center.y - circle[i].y),
                 40);
    output_space((center.x - circle[i].x * 2) - 1, (center.y - circle[i].y),
                 40);
  }

  output_space(center.x, center.y, 40);
}

void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14],
                  const std::vector<Coordinates> &circle_tick) {

  for (int i = 0; i < 14; i++) {
    i += (i == 4 || i == 9);
    output_char(center.x + tick[i].x, center.y - tick[i].y, '.');
  }

  for (int i = 13; i >= 0; i--) {
    i -= (i == 4 || i == 9);
    output_char(center.x + tick[i].x, center.y + tick[i].y, '.');
  }

  for (int i = 0; i < 14; i++) {
    i += (i == 4 || i == 9);
    output_char(center.x - tick[i].x, center.y + tick[i].y, '.');
  }

  for (int i = 13; i >= 0; i--) {
    i -= (i == 4 || i == 9);
    output_char(center.x - tick[i].x, center.y - tick[i].y, '.');
  }
  /*
    std::cout << "12 : y: " << center.y - circle_tick[0].y
              << "; x: " << center.x - 1 << "\n";
    std::cout << "3  : y: " << center.y
              << "; x: " << center.x + circle_tick[circle_tick.size() - 1].x
              << "\n";
    std::cout << "6  : y: " << center.y + circle_tick[0].y << "; x: " <<
    center.x
              << "\n";
    std::cout << "9  : y: " << center.y
              << "; x: " << center.x - circle_tick[circle_tick.size() - 1].x - 1
              << "\n";
  */

  output_char(center.x + tick[4].x, center.y - tick[4].y, '1');
  output_char(center.x + tick[9].x, center.y - tick[9].y, '2');
  output_char(center.x + circle_tick[circle_tick.size() - 1].x, center.y, '3');

  output_char(center.x + tick[9].x, center.y + tick[9].y, '4');
  output_char(center.x + tick[4].x, center.y + tick[4].y, '5');
  output_char(center.x, center.y + circle_tick[0].y, '6');

  output_char(center.x - tick[4].x, center.y + tick[4].y, '7');
  output_char(center.x - tick[9].x, center.y + tick[9].y, '8');
  output_char(center.x - circle_tick[circle_tick.size() - 1].x - 1, center.y,
              '9');

  output_char(center.x - tick[9].x, center.y - tick[9].y, '1');
  output_char(center.x - tick[9].x + 1, center.y - tick[9].y, '0');
  output_char(center.x - tick[4].x, center.y - tick[4].y, '1');
  output_char(center.x - tick[4].x + 1, center.y - tick[4].y, '1');
  output_char(center.x - 1, center.y - circle_tick[0].y, '1');
  output_char(center.x, center.y - circle_tick[0].y, '2');
}

void test_function(const std::vector<Coordinates> &circle,
                   const std::vector<Coordinates> &circle_tick,
                   const Coordinates (&tick)[14]) {
  for (size_t i = 0; i < circle.size(); i++) {
    std::cout << "\033[30mX" << i << " : " << circle[i].x << "  \tY" << i
              << " : " << circle[i].y << "\n";
  }
  std::cout << "============================================\n";
  for (size_t i = 0; i < circle_tick.size(); i++) {
    std::cout << "X" << i << " : " << circle_tick[i].x << "  \tY" << i << " : "
              << circle_tick[i].y << "\n";
  }
  std::cout << "============================================\n";
  for (int i = 0; i < 14; i++) {
    std::cout << "X" << i << " : " << tick[i].x << "  \tY" << i << " : "
              << tick[i].y << "\n";
  }
}

void watch_face(const int &size_x, const int &size_y) {
  Coordinates center;
  int radius;
  std::vector<Coordinates> circle;
  Coordinates tick[14];
  std::vector<Coordinates> circle_tick;

  Coordinate_center(center, size_x, size_y);

  Radius(radius, size_x, size_y);

  Coordinates_circle(radius, circle);

  draw_circle(center, circle);

  radius--;
  Coordinates_circle(radius, circle_tick);

  Coordinate_upgrade(circle_tick);

  Calculation_degrees(tick, circle_tick);

  //  test_function(circle, circle_tick, tick);

  draw_numbers(center, tick, circle_tick);
}
