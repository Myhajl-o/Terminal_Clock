#include "Hour-hand.hpp"
#include "Coordinates.hpp"
#include "Color_object.hpp"
#include "output.h"
#include "math.hpp"
#include "timedate.hpp"
#include <vector>

Hour_hand::Hour_hand(const short wi,const Color_object*draw_c,const Color_object clear_c,const char* const*sym,const bool show_min_circ)
{
  width = wi;
  draw_color = draw_c[0];
  mini_circle_color = draw_c[1];
  clear_color = clear_c;
  symbols = sym;
  show_mini_circle = show_min_circ;
  current_hour = 60;
  clearing = false;
  drawing = false;
}

void Hour_hand::update(const Coordinates &new_size,const Color_object*draw_c,const Color_object clear_c)
{
  draw_color = draw_c[0];
  mini_circle_color = draw_c[1];
  clear_color = clear_c;
  clearing = false;
  drawing = true;
  Coordinate_center(center, new_size);
  Calculation_radius(radius, 5, center,width);
  Coordinates_circle(circle_hour,radius);
  Coordinate_upgrade(circle_hour,width);
  Coordinate_degree(hour_tick[0],30,circle_hour);
  Coordinate_degree(hour_tick[1],60,circle_hour);

  if(show_mini_circle)
  {
    mini_radius = radius / 5;
    mini_shift = radius / 3;
    Coordinates_circle(temp_circle,mini_shift);
    Coordinate_upgrade(temp_circle,width);
    Coordinate_degree(mini_tick[0],30,temp_circle);
    Coordinate_degree(mini_tick[1],60,temp_circle);
  }
}


bool Hour_hand::second_update()
{
  short temp = cur_second();
  return (current_second != temp) ? (current_second = temp, true) : false;
}


bool Hour_hand::hour_update(const bool flag)
{
  short temp = (cur_hour() % 12);
  if(flag)
  {
    return (current_hour != temp) ? (current_hour = temp, true) : false;
  }
  return current_hour != temp;
}


void Hour_hand::calculation_coordinate_line()
{
  short temp = current_hour % 3;
  
  if (temp == 0)
  {
    line.clear();
    Coordinates value(0, 1);
    short dilatation = 1;
    if (current_hour == 3 || current_hour == 9)
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
    temp = (current_hour > 3 && current_hour < 6) ||
           (current_hour > 9 && current_hour < 12) ? 3 - temp : temp;
    hour_stop = hour_tick[temp - 1];
    hour_stop.x += current_hour > 6;
    Coordinates_line(line,hour_stop);
  }
  if(show_mini_circle)
  {
    calculation_mini_circle(temp);
  }
}

void Hour_hand::calculation_mini_circle(short temp)
{
  if(temp == 0)
  {
    if(current_hour == 0 || current_hour == 6)
    {
      mini_center.reset(0,mini_shift);
    }
    else
    {
      mini_center.reset(mini_shift * width, 0);
    }
  }
  else
  {
    mini_center = mini_tick[temp - 1];
    mini_center.x += current_hour > 6;
  }
  Coordinates_circle(mini_circle,mini_radius);
  Coordinate_upgrade(mini_circle,width);
}


short Hour_hand::current_symbol(const unsigned short &i)
{
  short diagonal = (current_hour < 16 || (current_hour > 30 && current_hour < 45)) ? 1 : 2;
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


void Hour_hand::draw()
{
  if(hour_update(true) || drawing)
  {
    calculation_coordinate_line();
    shift.x = (current_hour < 7) ? 1 : -1;
    shift.y = (current_hour > 3 && current_hour < 10) ? 1 : -1;
  }
  if(second_update() || drawing)
  {
    for(unsigned short i = 0; i < line.size(); i++)
    {
      output_object(center.x + line[i].x * shift.x, center.y + line[i].y * shift.y, symbols[current_symbol(i)], draw_color.c);
    }

    if(show_mini_circle)
    {
      for(unsigned short i = 0; i < mini_circle.size(); i++)
      {
        output_object(center.x + (mini_center.x + mini_circle[i].x) * shift.x,center.y + (mini_center.y - mini_circle[i].y) * shift.y,symbols[4],mini_circle_color.c);
        output_object(center.x + (mini_center.x + mini_circle[i].x) * shift.x,center.y + (mini_center.y + mini_circle[i].y) * shift.y,symbols[4],mini_circle_color.c);
        output_object(center.x + (mini_center.x - mini_circle[i].x) * shift.x,center.y + (mini_center.y + mini_circle[i].y) * shift.y,symbols[4],mini_circle_color.c);
        output_object(center.x + (mini_center.x - mini_circle[i].x) * shift.x,center.y + (mini_center.y - mini_circle[i].y) * shift.y,symbols[4],mini_circle_color.c);
      }
    }
    clearing = true;
    drawing = false;
  }
}


void Hour_hand::clear()
{
  if(hour_update(false) && clearing)
  {
    for (unsigned short i = 0; i < line.size(); i++)
    {
      output_object(center.x + line[i].x * shift.x,center.y + line[i].y * shift.y, symbols[5], clear_color.c);
    }
    if(show_mini_circle)
    {
      for(unsigned short i = 0; i < mini_circle.size(); i++)
      {
        output_object(center.x + (mini_center.x + mini_circle[i].x) * shift.x,center.y + (mini_center.y - mini_circle[i].y) * shift.y,symbols[5],clear_color.c);
        output_object(center.x + (mini_center.x + mini_circle[i].x) * shift.x,center.y + (mini_center.y + mini_circle[i].y) * shift.y,symbols[5],clear_color.c);
        output_object(center.x + (mini_center.x - mini_circle[i].x) * shift.x,center.y + (mini_center.y + mini_circle[i].y) * shift.y,symbols[5],clear_color.c);
        output_object(center.x + (mini_center.x - mini_circle[i].x) * shift.x,center.y + (mini_center.y - mini_circle[i].y) * shift.y,symbols[5],clear_color.c);
      }
    }
  }
}
