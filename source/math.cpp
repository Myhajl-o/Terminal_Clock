#include "math.hpp"
#include "Coordinates.hpp"
#include <cmath>
#include <vector>

const float convert = 180.0f / M_PI;

void Coordinate_center(Coordinates &center, const Coordinates &size)
{
  center = Coordinates{size.x / 2, size.y / 2};
}

void Radius(int &radius, int backdown, const Coordinates &center)
{
  if (center.x < (center.y * 2))
  {
    radius = (center.x / 2) - backdown;
  }
  else
  {
    radius = center.y - backdown;
  }
}

void Coordinates_circle(const int &radius, std::vector<Coordinates> &circle)
{
  circle.clear();
  int d = 3 - 2 * radius;
  Coordinates temp = Coordinates{0, radius};
  circle.push_back(temp);

  do
  {
    if (d < 0)
    {
      d = d + 4 * temp.x + 6;
      temp.x++;
      circle.push_back(temp);
    }
    else
    {
      d = d + 4 * (temp.x - temp.y) + 10;
      temp.x++;
      temp.y--;
      circle.push_back(temp);
    }
  } while (temp.x == temp.y || temp.x < temp.y);

  circle.resize(temp.x * 2);
  for (int j = temp.x * 2 - 1; j >= temp.x; j--)
  {
    circle[j].x = circle[(temp.x * 2 - 1) - j].y;
    circle[j].y = circle[(temp.x * 2 - 1) - j].x;
  }
}

void Coordinate_upgrade(std::vector<Coordinates> &circle)
{
  std::vector<Coordinates> temp = circle;
  circle.resize(circle.size() * 2 - 1);
  int j = 0;
  int add;

  for (size_t i = 0; i < circle.size(); i += 2)
  {
    add = temp[j].x < temp[j + 1].x;

    circle[i].x = temp[j].x * 2;
    circle[i].y = temp[j].y;

    circle[i + 1].x = temp[j].x * 2 + add;
    circle[i + 1].y = temp[j].y;
    j++;
  }
}

void Degree(int degree, Coordinates &tick_element, const std::vector<Coordinates> &circle)
{
  float difference[2];
  difference[0] = std::abs(degree - (convert * std::atan2((float)circle[1].x, (float)circle[1].y * 2)));

  for (size_t i = 2; i < circle.size(); i++)
  {
    difference[1] = std::abs(degree - (convert * std::atan2((float)circle[i].x, (float)circle[i].y * 2)));
    if (difference[0] < difference[1])
    {
      tick_element = circle[i - 1];
      return;
    }
    difference[0] = difference[1];
  }
}

void Calculation_degrees(Coordinates (&tick)[14], const std::vector<Coordinates> &circle)
{
  for (int i = 0; i < 14; i++)
  {
    Degree((i + 1) * 6, tick[i], circle);
  }
}

void Coordinates_line(const Coordinates &B, std::vector<Coordinates> &line)
{
  line.clear();
  Coordinates temp = {0, 0};
  Coordinates delta = (B.x < B.y) ? Coordinates{B.y, B.x} : Coordinates{B.x, B.y};
  Coordinates add = (B.x < B.y) ? Coordinates{0, 1} : Coordinates{1, 0};

  int d = 2 * delta.y - delta.x;

  do
  {
    if (d < 0)
    {
      temp.x += add.x;
      temp.y += add.y;
      line.push_back(temp);
      d = d + 2 * delta.y;
    }
    else
    {
      temp.x++;
      temp.y++;
      line.push_back(temp);
      d = d + 2 * delta.y - 2 * delta.x;
    }
  } while (temp != B);
}
