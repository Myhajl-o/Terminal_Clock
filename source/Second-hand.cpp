#include "Second-hand.hpp"
#include "Coordinates.hpp"
#include "Color_object.hpp"
#include "math.hpp"
#include "output.h"
#include "timedate.hpp"
#include <vector>

Second_hand::Second_hand(const short wi,const Color_object draw_c,const Color_object clear_c,const char* const*sym)
{
  width = wi;
  draw_color = draw_c;
  clear_color = clear_c;
  symbols = sym;
  current_second = 60;
  clearing = false;
  drawing = false;
}

// The update method of the Second_hand class updates the class fields
// relative to the new size, and calculates some of them
// for the correct output of the second hand.
//
// The method is used in the heart_clock.cpp file.
void Second_hand::update(const Coordinates &new_size,const Color_object draw_c,const Color_object clear_c)
{
  draw_color = draw_c;
  clear_color = clear_c;
  clearing = false;
  drawing = true;
  Coordinate_center(center, new_size);
  Calculation_radius(radius, 3, center,width);
  Coordinates_circle(circle_second,radius);
  Coordinate_upgrade(circle_second,width);
  Coordinate_circle_degrees(second_tick,circle_second,width);
}

// The second_update method of the Second_hand class retrieves data about
// the current second from the system and updates the class fields.
// It is used as an internal indicator that the state of the
// second hand needs to be updated.
//
// The method is used in the draw method.
bool Second_hand::second_update(bool flag)
{
  short temp = cur_second();
  if (flag)
  {
    return (current_second != temp) ? (current_second = temp, true) : false;
  }
  return current_second != temp;
}

// The calculation_coordinate_line method of the Second_hand class
// calculates the coordinates for drawing the hand, which during the calculation
// are adapted to a full circle.
//
// The method is used in the draw method.
void Second_hand::calculation_coordinate_line()
{
  short temp = current_second % 15;
  if (temp == 0)
  {
    line.clear();
    Coordinates value(0, 1);
    short dilatation = 1;
    if (current_second == 15 || current_second == 45)
    {
      value.reset(1, 0);
      dilatation = width;
    }
    for (short i = 1; i <= radius * dilatation; i++)
    {
      line.push_back(Coordinates(i * value.x, i * value.y));
    }
  }
  else
  {
    temp = ((current_second > 15 && current_second < 30) ||
            (current_second > 45 && current_second < 60)) ? 15 - temp : temp;
    second_stop = second_tick[temp - 1];
    second_stop.x += current_second > 30;
    Coordinates_line(line,second_stop);
  }
}

// The current_symbol method of the Second_hand class determines the specific
// symbol for a specific coordinate of the second hand.
//
// The method is used in the draw method.
short Second_hand::current_symbol(const unsigned short &i)
{
  short diagonal = (current_second < 16 || (current_second > 30 && current_second < 45)) ? 1 : 2;
  if (i == 0)
  {
    return (line[i].x == line[i + 1].x)   ? 0 : (line[i].y == line[i + 1].y) ? 3 : diagonal;
  }
  else if (i == line.size() - 1)
  {
    return (line[i].x == line[i - 1].x)   ? 0 : (line[i].y == line[i - 1].y) ? 3 : diagonal;
  }
  else
  {
    if (line[i - 1].x == line[i].x && line[i].x == line[i + 1].x)
    {
      return 0;
    }
    else if (line[i - 1].y == line[i].y && line[i].y == line[i + 1].y)
    {
      return 3;
    }
    else
    {
      return diagonal;
    }
  }
}

// The draw method of the Second_hand class calculates the coordinates and
// outputs the second hand. It redraws it
// every time the second changes, when the size of the terminal
// window changes, and when the output color changes.
//
// The method is used in the heart_clock.cpp file.
void Second_hand::draw()
{
  if (second_update(true) || drawing)
  {
    calculation_coordinate_line();
    shift.x = (current_second < 31) ? 1 : -1;
    shift.y = (current_second > 15 && current_second < 46) ? 1 : -1;

    for (unsigned short i = 0; i < line.size(); i++)
    {
      output_object(center.x + line[i].x * shift.x, center.y + line[i].y * shift.y, symbols[current_symbol(i)], draw_color.c);
    }
    clearing = true;
    drawing = false;
  }
}

// The clear method of the Second_hand class outputs spaces
// at the exact same coordinates where the previous hand was,
// to erase it. It outputs spaces only when the
// second changes, but not immediately after the terminal
// size or its color has changed.
//
// The method is used in the heart_clock.cpp file.
void Second_hand::clear()
{
  if (second_update(false) && clearing)
  {
    for (unsigned short i = 0; i < line.size(); i++)
    {
      output_object(center.x + line[i].x * shift.x,center.y + line[i].y * shift.y, symbols[4], clear_color.c);
    }
  }
}
