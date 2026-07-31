#include "watch_face.hpp"
#include "Coordinates.hpp"
#include "math.hpp"
#include "output.hpp"
#include <vector>

void calculate_data_circle(const Coordinates &size, Coordinates &center, short &radius, std::vector<Coordinates> &circle)
{
  Coordinate_center(center, size);
  Calculation_radius(radius, 1, center);
  Coordinates_circle(radius, circle);
}

void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle)
{
  char space[4] = "  \0";

  for (unsigned short i = 0; i < circle.size(); i++)
  {
    output_symbols(center.x + circle[i].x * 2, (center.y - circle[i].y), space, true);
    output_symbols(center.x + circle[i].x * 2, (center.y + circle[i].y), space, true);
    output_symbols((center.x - circle[i].x * 2) - 2, (center.y + circle[i].y), space, true);
    output_symbols((center.x - circle[i].x * 2) - 2, (center.y - circle[i].y), space, true);
  }

  output_symbols(center.x, center.y, &space[1], true);
}
void calculate_data_numbers(short &radius, std::vector<Coordinates> &circle_tick, Coordinates (&tick)[14])
{
  radius--;
  Coordinates_circle(radius, circle_tick);
  Coordinate_upgrade(circle_tick);
  for (short i = 0; i < 14; i++)
  {
    Coordinate_degree((i + 1) * 6, tick[i], circle_tick);
  }
}

void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14], const std::vector<Coordinates> &circle_tick)
{
  const char *char_tick[] = {".\0", "1\0", "2\0", "12\0", "5\0", "4\0", "3\0",
                             "7\0", "8\0", "6\0", "11\0", "10\0", "9\0"};
  for (short i = 0; i < 14; i++)
  {
    i += (i == 4 || i == 9);
    output_symbols(center.x + tick[i].x, center.y - tick[i].y, char_tick[0], false);
    output_symbols(center.x + tick[i].x, center.y + tick[i].y, char_tick[0], false);
    output_symbols(center.x - tick[i].x - 1, center.y + tick[i].y, char_tick[0], false);
    output_symbols(center.x - tick[i].x - 1, center.y - tick[i].y, char_tick[0], false);
  }
  output_symbols(center.x + tick[4].x, center.y - tick[4].y, char_tick[1], false);
  output_symbols(center.x + tick[9].x, center.y - tick[9].y, char_tick[2], false);
  output_symbols(center.x - 1, center.y - circle_tick[0].y, char_tick[3], false);

  output_symbols(center.x + tick[4].x, center.y + tick[4].y, char_tick[4], false);
  output_symbols(center.x + tick[9].x, center.y + tick[9].y, char_tick[5], false);
  output_symbols(center.x + circle_tick[0].y * 2, center.y, char_tick[6], false);

  output_symbols(center.x - tick[4].x - 1, center.y + tick[4].y, char_tick[7], false);
  output_symbols(center.x - tick[9].x - 1, center.y + tick[9].y, char_tick[8], false);
  output_symbols(center.x, center.y + circle_tick[0].y, char_tick[9], false);

  output_symbols(center.x - tick[4].x - 1, center.y - tick[4].y, char_tick[10], false);
  output_symbols(center.x - tick[9].x - 1, center.y - tick[9].y, char_tick[11], false);
  output_symbols(center.x - circle_tick[0].y * 2 - 1, center.y, char_tick[12], false);
}

void draw_watch_face(const Coordinates &size)
{
  Coordinates center;
  short radius;
  std::vector<Coordinates> circle;
  Coordinates tick[14];
  std::vector<Coordinates> circle_tick;

  calculate_data_circle(size, center, radius, circle);

  draw_circle(center, circle);

  calculate_data_numbers(radius, circle_tick, tick);

  draw_numbers(center, tick, circle_tick);
}
