#include "Minute-hand.hpp"
#include "Coordinates.hpp"
#include "Color_object.hpp"
#include "output.h"
#include "math.hpp"
#include "timedate.hpp"
#include <vector>

Minute_hand::Minute_hand(const short wi,const Color_object draw_c,const Color_object clear_c,const char* const*sym)
{
  width = wi;
  draw_color = draw_c;
  clear_color = clear_c;
  symbols = sym;
  current_minute = 60;
  clearing = false;
  drawing = false;
}

void Minute_hand::update(const Coordinates &new_size,const Color_object draw_c,const Color_object clear_c)
{
  draw_color = draw_c;
  clear_color = clear_c;
  clearing = false;
  drawing = true;
  Coordinate_center(center, new_size);
  Calculation_radius(radius, 4, center,width);
  Coordinates_circle(circle_minute,radius);
  Coordinate_upgrade(circle_minute,width);
  Coordinate_circle_degrees(minute_tick,circle_minute,width);
}


bool Minute_hand::second_update()
{
  short temp = cur_second();
    return (current_second != temp) ? (current_second = temp, true) : false;
}


bool Minute_hand::minute_update(const bool flag)
{
  short temp = cur_minute();
  if(flag)
  {
    return (current_minute != temp) ? (current_minute = temp, true) : false;
  }
  return current_minute != temp;
}

void Minute_hand::calculation_coordinate_line()
{
  short temp = current_minute % 15;
  if (temp == 0)
  {
    line.clear();
    Coordinates value(0, 1);
    short dilatation = 1;
    if (current_minute == 15 || current_minute == 45)
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
    temp = ((current_minute > 15 && current_minute < 30) ||
            (current_minute > 45 && current_minute < 60)) ? 15 - temp : temp;
    minute_stop = minute_tick[temp - 1];
    minute_stop.x += current_minute > 30;
    Coordinates_line(line,minute_stop);
  }
}

short Minute_hand::current_symbol(const unsigned short &i)
{
  short diagonal = (current_minute < 16 || (current_minute > 30 && current_minute < 45)) ? 1 : 2;
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


void Minute_hand::draw()
{
  if(minute_update(true) || drawing)
  {
    calculation_coordinate_line();
    shift.x = (current_minute < 31) ? 1 : -1;
    shift.y = (current_minute > 15 && current_minute < 46) ? 1 : -1;
  }
  if(second_update() || drawing)
  {
    for (unsigned short i = 0; i < line.size(); i++)
    {
      output_object(center.x + line[i].x * shift.x, center.y + line[i].y * shift.y, symbols[current_symbol(i)], draw_color.c);
    }
    clearing = true;
    drawing = false;
  }
}

void Minute_hand::clear()
{
  if(minute_update(false) && clearing)
  {
    for (unsigned short i = 0; i < line.size(); i++)
    {
      output_object(center.x + line[i].x * shift.x,center.y + line[i].y * shift.y, symbols[4], clear_color.c);
    }
  }
}
