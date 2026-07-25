#include "output.hpp"
#include "Coordinates.hpp"
#include "math.hpp"
#include <iostream>
#include <string>
#include <vector>

void clear()
{
  std::cout << "\033[0m" << std::flush;
  system("clear");
}

void output_string(const int &x, const int &y, const char *s, int color)
{
  std::cout << "\033[" << color << "m\033[" << y << ";" << x << "H" << s << "\033[47m" << std::flush;
}

void background(const Coordinates &size)
{
  std::string canvas(size.x * size.y, ' ');
  std::cout << "\033[47m" << canvas;
}

void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle)
{
  char space[3] = "  ";
  for (int i = 0; i < 4; i++)
  {
    int size = (i == 1 || i == 3) ? circle.size() - 1 : circle.size() - 2;
    Coordinates shift = (i == 0) ? Coordinates{1, -1} : (i == 1) ? Coordinates{1, 1}
                                                    : (i == 2)   ? Coordinates{-1, 1}
                                                                 : Coordinates{-1, -1};
    Coordinates change_index = (i == 1 || i == 3) ? Coordinates{size, 1} : Coordinates{0, -1};
    int dilatation = (i > 1) ? 2 : 0;
    for (int i = 0; i <= size; i++)
    {
      output_string((center.x + circle[change_index.x - i * change_index.y].x * 2 * shift.x) - dilatation, (center.y + circle[change_index.x - i * change_index.y].y * shift.y), space, 40);
    }
  }
  output_string(center.x, center.y, &space[1], 40);
}

void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14],
                  const std::vector<Coordinates> &circle_tick)
{
  const char *char_tick[] = {".", "1", "2", "12", "4", "5", "3", "7", "8", "6", "10", "11", "9"};
  for (int i = 0; i < 4; i++)
  {
    Coordinates shift = (i == 0) ? Coordinates{1, -1} : (i == 1) ? Coordinates{1, 1}
                                                    : (i == 2)   ? Coordinates{-1, 1}
                                                                 : Coordinates{-1, -1};
    int dilatation = (i > 1) ? 1 : 0;
    Coordinates change_index = (i == 1 || i == 3) ? Coordinates{13, 1} : Coordinates{0, -1};
    Coordinates flag = (i == 0 || i == 2) ? Coordinates{0, 1} : Coordinates{1, 0};
    for (int j = 0; j < 14; j++)
    {
      output_string(center.x + tick[change_index.x - j * change_index.y].x * shift.x - dilatation, center.y + tick[change_index.x - j * change_index.y].y * shift.y, char_tick[(j == 4) ? (i * 3) + 1 : (j == 9) ? (i * 3) + 2
                                                                                                                                                                                                                 : 0],
                    30);
    }
    output_string(center.x + circle_tick[0].y * 2 * shift.x * flag.x - dilatation, center.y + circle_tick[0].y * shift.y * flag.y, char_tick[(i * 3) + 3], 30);
  }
}

void watch_face(const Coordinates &size)
{
  Coordinates center;
  int radius;
  std::vector<Coordinates> circle;
  Coordinates tick[14];
  std::vector<Coordinates> circle_tick;

  Coordinate_center(center, size);
  Radius(radius, 1, center);
  Coordinates_circle(radius, circle);
  draw_circle(center, circle);
  radius--;
  Coordinates_circle(radius, circle_tick);
  Coordinate_upgrade(circle_tick);
  Calculation_degrees(tick, circle_tick);
  draw_numbers(center, tick, circle_tick);
}
