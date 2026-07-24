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

void output_two_char(const int &x, const int &y, const char s[], int color)
{
  std::cout << "\033[" << color << "m\033[" << y << ";" << x << "H" << s
            << "\033[47m" << std::flush;
}

void output_char(const int &x, const int &y, char c, int color)
{
  std::cout << "\033[" << color << "m\033[" << y << ";" << x << "H" << c
            << "\033[47m" << std::flush;
}

void background(const int &x, const int &y)
{
  std::string canvas(x * y, ' ');
  std::cout << "\033[47m" << canvas;
}

void draw_circle(const Coordinates &center,
                 const std::vector<Coordinates> &circle)
{
  for (std::size_t i = 0; i < circle.size(); i++)
  {
    output_two_char((center.x + circle[i].x * 2), (center.y - circle[i].y),
                    "  ", 40);
  }
  for (int i = circle.size() - 2; i >= 0; i--)
  {
    output_two_char((center.x + circle[i].x * 2), (center.y + circle[i].y),
                    "  ", 40);
  }
  for (std::size_t i = 0; i < circle.size(); i++)
  {
    output_two_char((center.x - circle[i].x * 2) - 2, (center.y + circle[i].y),
                    "  ", 40);
  }
  for (int i = circle.size() - 2; i >= 0; i--)
  {
    output_two_char((center.x - circle[i].x * 2) - 2, (center.y - circle[i].y),
                    "  ", 40);
  }
  output_char(center.x, center.y, ' ', 40);
}

void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14],
                  const std::vector<Coordinates> &circle_tick)
{

  for (int i = 0; i < 14; i++)
  {
    i += (i == 4 || i == 9);
    output_char(center.x + tick[i].x, center.y - tick[i].y, '.', 30);
  }

  for (int i = 13; i >= 0; i--)
  {
    i -= (i == 4 || i == 9);
    output_char(center.x + tick[i].x, center.y + tick[i].y, '.', 30);
  }

  for (int i = 0; i < 14; i++)
  {
    i += (i == 4 || i == 9);
    output_char(center.x - tick[i].x - 1, center.y + tick[i].y, '.', 30);
  }

  for (int i = 13; i >= 0; i--)
  {
    i -= (i == 4 || i == 9);
    output_char(center.x - tick[i].x - 1, center.y - tick[i].y, '.', 30);
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

  output_char(center.x + tick[4].x, center.y - tick[4].y, '1', 30);
  output_char(center.x + tick[9].x, center.y - tick[9].y, '2', 30);
  output_char(center.x + circle_tick[0].y * 2, center.y, '3', 30);

  output_char(center.x + tick[9].x, center.y + tick[9].y, '4', 30);
  output_char(center.x + tick[4].x, center.y + tick[4].y, '5', 30);
  output_char(center.x, center.y + circle_tick[0].y, '6', 30);

  output_char(center.x - tick[4].x - 1, center.y + tick[4].y, '7', 30);
  output_char(center.x - tick[9].x - 1, center.y + tick[9].y, '8', 30);
  output_char(center.x - circle_tick[0].y * 2 - 1, center.y, '9', 30);

  output_two_char(center.x - tick[9].x - 1, center.y - tick[9].y, "10", 30);
  output_two_char(center.x - tick[4].x - 1, center.y - tick[4].y, "11", 30);
  output_two_char(center.x - 1, center.y - circle_tick[0].y, "12", 30);
}

void test_function(const std::vector<Coordinates> &circle)
{
  for (size_t i = 0; i < circle.size(); i++)
  {
    std::cout << "\033[30mZ" << i << " : " << circle[i].x << "  \tY" << i << " : " << circle[i].y << "\n"
              << std::flush;
  }
  /*
  std::cout << "============================================\n";
  for (size_t i = 0; i < circle_tick.size(); i++)
  {
    std::cout << "X" << i << " : " << circle_tick[i].x << "  \tY" << i << " : "
              << circle_tick[i].y << "\n";
  }
  std::cout << "============================================\n";
  for (int i = 0; i < 14; i++)
  {
    std::cout << "X" << i << " : " << tick[i].x << "  \tY" << i << " : "
              << tick[i].y << "\n";
  }
  */
}
/*
void test_function1(const Coordinates ass)
{
  std::cout << "\033[30mX : " << ass.x << "  \t Y : " << ass.y << "\n";
}
*/
void watch_face(const int &size_x, const int &size_y)
{
  Coordinates center;
  int radius;
  std::vector<Coordinates> circle;
  Coordinates tick[14];
  std::vector<Coordinates> circle_tick;

  Coordinate_center(center, size_x, size_y);

  Radius(radius, 1, size_x, size_y);

  Coordinates_circle(radius, circle);

  draw_circle(center, circle);

  radius--;
  Coordinates_circle(radius, circle_tick);

  Coordinate_upgrade(circle_tick);

  Calculation_degrees(tick, circle_tick);

  //  test_function(circle, circle_tick, tick);

  draw_numbers(center, tick, circle_tick);
}
