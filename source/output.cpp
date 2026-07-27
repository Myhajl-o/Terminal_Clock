#include "output.hpp"
#include "Coordinates.hpp"
#include "math.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern bool color;
short main_color;
short secondary_color;
short symbol_color;

void change_color()
{
  if (color)
  {
    main_color = 40;
    secondary_color = 47;
    symbol_color = 37;
  }
  else
  {
    main_color = 47;
    secondary_color = 40;
    symbol_color = 30;
  }
}

void clear()
{
  printf("\033[0m");
  std::system("clear");
}

void output_symbols(short x, short y, const char *s, bool other_color)
{
  if (other_color)
  {
    printf("\033[%dm\033[%d;%dH%s\033[%dm", secondary_color, y, x, s,
           main_color);
  }
  else
  {
    printf("\033[%d;%dH%s", y, x, s);
  }
  fflush(stdout);
}

void background(const Coordinates &size)
{
  change_color();
  std::string canvas(size.x * size.y, ' ');
  printf("\033[%dm\033[%dm%s", main_color, symbol_color, canvas.c_str());
}

void draw_circle(const Coordinates &center,
                 const std::vector<Coordinates> &circle)
{
  char space[3] = "  ";
  short size[4] = {(short)(circle.size() - 2), (short)(circle.size() - 1),
                   (short)(circle.size() - 2), (short)(circle.size() - 1)};
  Coordinates shift[4] = {Coordinates(1, -1), Coordinates(1, 1),
                          Coordinates(-1, 1), Coordinates(-1, -1)};
  short dilatation[4] = {0, 0, 2, 2};

  for (short i = 0; i < 4; i++)
  {
    for (short j = 0; j <= size[i]; j++)
    {
      output_symbols((center.x + circle[j].x * 2 * shift[i].x) - dilatation[i],
                     (center.y + circle[j].y * shift[i].y), space, true);
    }
  }
  output_symbols(center.x, center.y, &space[1], true);
}

void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14],
                  const std::vector<Coordinates> &circle_tick)
{
  const char *char_tick[] = {".", "1", "2", "12", "5", "4", "3",
                             "7", "8", "6", "11", "10", "9"};
  Coordinates shift[4] = {Coordinates(1, -1), Coordinates(1, 1),
                          Coordinates(-1, 1), Coordinates(-1, -1)};
  short dilatation[7] = {0, 0, 1, 1, 0, 0, 1};
  Coordinates flag[4] = {Coordinates(0, 1), Coordinates(1, 0),
                         Coordinates(0, 1), Coordinates(1, 0)};

  for (short i = 0; i < 4; i++)
  {
    for (short j = 0; j < 14; j++)
    {
      j += (j == 4 || j == 9);
      output_symbols(center.x + tick[j].x * shift[i].x - dilatation[i],
                     center.y + tick[j].y * shift[i].y, char_tick[0], false);
    }
  }

  for (short i = 0; i < 4; i++)
  {
    output_symbols(center.x + tick[4].x * shift[i].x - dilatation[i],
                   center.y + tick[4].y * shift[i].y, char_tick[(i * 3) + 1],
                   false);
    output_symbols(center.x + tick[9].x * shift[i].x - dilatation[i],
                   center.y + tick[9].y * shift[i].y, char_tick[(i * 3) + 2],
                   false);
    output_symbols(center.x + circle_tick[0].y * 2 * shift[i].x * flag[i].x -
                       dilatation[i + 3],
                   center.y + circle_tick[0].y * shift[i].y * flag[i].y,
                   char_tick[(i * 3) + 3], false);
  }
}
/*
void daw_numbers(const Coordinates &center, const Coordinates (&tick)[14],
                 const std::vector<Coordinates> &circle_tick) {
  const char *char_tick[] = {".", "1", "2", "12", "5",  "4", "3",
                             "7", "8", "6", "11", "10", "9"};
  for (int j = 0; j < 14; j++) {
    j += (j == 4 || j == 9);
    output_string(center.x + tick[j].x, center.y - tick[j].y, char_tick[0], 30);
  }
  for (int j = 0; j < 14; j++) {
    j += (j == 4 || j == 9);
    output_string(center.x + tick[j].x, center.y + tick[j].y, char_tick[0], 30);
  }
  for (int j = 0; j < 14; j++) {
    j += (j == 4 || j == 9);
    output_string(center.x - tick[j].x - 1, center.y + tick[j].y, char_tick[0],
                  30);
  }
  for (int j = 0; j < 14; j++) {
    j += (j == 4 || j == 9);
    output_string(center.x - tick[j].x - 1, center.y - tick[j].y, char_tick[0],
                  30);
  }

  output_string(center.x + tick[4].x, center.y - tick[4].y, char_tick[1], 30);
  output_string(center.x + tick[9].x, center.y - tick[9].y, char_tick[2], 30);
  output_string(center.x - 1, center.y - circle_tick[0].y, char_tick[3], 30);

  output_string(center.x + tick[4].x, center.y + tick[4].y, char_tick[4], 30);
  output_string(center.x + tick[9].x, center.y + tick[9].y, char_tick[5], 30);
  output_string(center.x + circle_tick[0].y * 2, center.y, char_tick[6], 30);

  output_string(center.x - tick[4].x, center.y + tick[4].y, char_tick[7], 30);
  output_string(center.x - tick[9].x, center.y + tick[9].y, char_tick[8], 30);
  output_string(center.x, center.y + circle_tick[0].y, char_tick[9], 30);

  output_string(center.x - tick[4].x, center.y - tick[4].y, char_tick[10], 30);
  output_string(center.x - tick[9].x, center.y - tick[9].y, char_tick[11], 30);
  output_string(center.x - circle_tick[0].y * 2 - 1, center.y, char_tick[12],
                30);
}
*/
void watch_face(const Coordinates &size)
{
  Coordinates center;
  short radius;
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
