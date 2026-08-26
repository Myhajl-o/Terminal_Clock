#include "math.hpp"
#include "Coordinates.hpp"
#include <cmath>
#include <vector>

const float convert = 180.0f / M_PI;

float absolute_number(float number)
{
  return (number < 0) ? -number : number;
}

// The Coordinate_center function is designed to calculate
// the center of the terminal window. The function calculates
// the center by dividing the terminal width by 2 and
// dividing the terminal height by 2.
//
// The function returns nothing, and writes the result
// into the variable passed to the function by reference.
//
// This function is used in the watch_face.cpp and
// Second-hand.cpp files.
void Coordinate_center(Coordinates &center, const Coordinates &size)
{
  center.reset(size.x / 2, size.y / 2);
}

// The Calculation_radius function calculates a radius that will
// fit the size of the terminal. For example, if the terminal width
// is less than the height, the radius will be calculated relative
// to the width rather than the height. This is done so that
// the circle drawn using this radius fits exactly into the
// terminal window.
//
// The function returns nothing, and writes the result
// into the variable passed to the function by reference.
//
// This function is used in the watch_face.cpp and
// Second-hand.cpp files.
void Calculation_radius(short &radius, short backdown, const Coordinates &center,const short width)
{
  if (center.x < (center.y * width))
  {
    radius = (center.x / width) - backdown;
  }
  else
  {
    radius = center.y - backdown;
  }
}

// The Coordinates_circle function calculates the coordinates for
// drawing a 1/4 circle relative to the initial coordinates
// x:0, y:0. That is, the function calculates raw data for
// drawing a 1/4 circle; to use them, certain mathematical
// calculations must be performed.
// The function first calculates a 1/8 circle using
// Bresenham's algorithm for drawing arcs or circles.
// The coordinates for the 1/4 circle are found by
// reflecting the previous coordinates that were
// obtained using Bresenham's algorithm.
//
// The function returns nothing, and writes the result
// into the variable passed to the function by reference.
//
// This function is used in the watch_face.cpp and
// Second-hand.cpp files.
void Coordinates_circle(std::vector<Coordinates> &circle,const short radius)
{
  circle.clear();
  short d = 3 - 2 * radius;
  Coordinates temp(0, radius);
  circle.push_back(temp);

  do
  {
    if (d < 0)
    {
      d = d + 4 * temp.x + 6;
      temp.x++;
    }
    else
    {
      d = d + 4 * (temp.x - temp.y) + 10;
      temp.x++;
      temp.y--;
    }
    circle.push_back(temp);
  } while (temp.x == temp.y || temp.x < temp.y);

  circle.resize(temp.x * 2);
  for (short i = temp.x * 2 - 1; i >= temp.x; i--)
  {
    circle[i].x = circle[(temp.x * 2 - 1) - i].y;
    circle[i].y = circle[(temp.x * 2 - 1) - i].x;
  }
}

// The Coordinate_upgrade function expands the coordinate array.
// It expands the array and increases the x coordinate.
// This is done to make the circle wider.
//
//! The function is designed for an array of 1/4 circle coordinates;
// if anything else is passed to it, the result may be incorrect.
//
// The function returns nothing, and writes the result
// into the variable passed to the function by reference.
//
// This function is used in the watch_face.cpp and
// Second-hand.cpp files.
void Coordinate_upgrade(std::vector<Coordinates> &circle,const short width)
{
  if(width == 1)
  {
    return;
  }
  static std::vector<Coordinates> temp;
  temp.clear();
  temp = circle;
  circle.resize(circle.size() * width - 1);
  short j = 0;
  short add;

  for (unsigned short i = 0; i < circle.size(); i += width)
  {
    add = temp[j].x < temp[j + 1].x;

    for(short add_i = 0; add_i < width; add_i++)
    {
      circle[i+add_i].x = temp[j].x * width + (add * add_i);
      circle[i+add_i].y = temp[j].y;
    }

    j++;
  }
}

// The Coordinate_degree function calculates the closest coordinate
// of the circle by its degree to the degree passed into the function.
// The degree of the coordinate is calculated relative to the zero
// coordinate (x:0, y:0), using the formula arctan(x / y).
// This function is used for building a watch face
// and for similar tasks.
//
// ! The function is designed for an array of 1/4 circle coordinates;
// if anything else is passed to it, the result may be incorrect.
//
// The function returns nothing, and writes the result
// into the variable passed to the function by reference.
//
// This function is used in the watch_face.cpp and
// Second-hand.cpp files.
void Coordinate_degree(Coordinates &tick_element,const short degree,const std::vector<Coordinates> &circle)
{
  float difference[2];
  unsigned short i;
  if(degree < 42)
  {
    i = 2;
  }
  else if(degree < 66)
  {
    i = circle.size() >> 2;
  }
  else
  {
    i = circle.size() >> 1;
  }

  difference[0] = absolute_number(degree - (convert * std::atan2((float)circle[1].x,(float)circle[1].y * 2)));

  while(i < circle.size())
  {
    difference[1] = absolute_number(degree - (convert * std::atan2((float)circle[i].x,(float)circle[i].y * 2)));
    if (difference[0] < difference[1])
    {
      tick_element = circle[i - 1];
      return;
    }
    difference[0] = difference[1];
    i++;
  }
}

void Coordinate_circle_degrees(Coordinates *ticks,const std::vector<Coordinates>&circle)
{
  float difference[2];
  static const short degrees[14] = {6,12,18,24,30,36,42,48,54,60,66,72,78,84};
  short i_deg = 0;
  difference[0] = absolute_number(degrees[0] - (convert * std::atan2((float)circle[1].x,(float)circle[1].y * 2)));

  for(unsigned short i = 2; i < circle.size() && i_deg < 14; i++)
  {
    difference[1] = absolute_number(degrees[i_deg] - (convert * std::atan2((float)circle[i].x,(float)circle[i].y * 2)));
    if(difference[0] < difference[1])
    {
      ticks[i_deg] = circle[i - 1];
      i_deg++;
      difference[0] = absolute_number(degrees[i_deg] - (convert * std::atan2((float)circle[i].x,(float)circle[i].y * 2)));
    }
    else
    {
      difference[0] = difference[1];
    }
  }

  while(i_deg < 14)
  {
    ticks[i_deg] = ticks[i_deg - 1];
    i_deg++;
  }
}

// The Coordinates_line function calculates the coordinates of a line segment
// that runs from the zero coordinate (x:0, y:0) to
// the passed coordinate B. The calculation is performed
// using Bresenham's line algorithm.
// The function is used in drawing watch hands.
//
// The function returns nothing, and writes the result
// into the variable passed to the function by reference.
//
// The function is used in the Second-hand.cpp file.
void Coordinates_line(std::vector<Coordinates> &line,const Coordinates &B)
{
  line.clear();
  Coordinates temp;
  Coordinates delta = B;
  Coordinates add(1, 0);
  if (B.x < B.y)
  {
    delta.reset(B.y, B.x);
    add.reset(0, 1);
  }

  short d = 2 * delta.y - delta.x;

  do
  {
    if (d < 0)
    {
      temp.x += add.x;
      temp.y += add.y;
      d = d + 2 * delta.y;
    }
    else
    {
      temp.x++;
      temp.y++;
      d = d + 2 * delta.y - 2 * delta.x;
    }
    line.push_back(temp);
  } while (temp != B);
}
