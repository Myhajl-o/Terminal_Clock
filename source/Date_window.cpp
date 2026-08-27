#include "Date_window.hpp"
#include "Coordinates.hpp"
#include "Color_object.hpp"
#include "math.hpp"
#include "timedate.hpp"
#include "output.h"
#include <stdlib.h>


Date_window::Date_window(const short wi,const Color_object*wind_c,const char*const*sym)
{
  spaces[0] = (char*)malloc(130);
  spaces[1] = (char*)malloc(33);
  spaces[2] = (char*)malloc(130);
  
  window_size[0].reset(32,8);
  window_size[1].reset(10,9);
  term_size.reset(0,0);
  current_day = 32;
  current_wday = 7;
  current_month = 13;
  current_year = 2077;
  show_window = false;
  
  width = wi;
  window_color[0] = wind_c[0];
  window_color[1] = wind_c[1];
  window_color[2] = wind_c[2];
  
  short size_sym = filling_space(spaces[0],sym[0],window_size[0].x);

  draw_sym[0] = spaces[0];
  draw_sym[1] = draw_sym[0] + 22 * size_sym;
  
  filling_space(spaces[1],sym[1],8);
  
  size_sym = filling_space(spaces[2],sym[2],window_size[0].x);
  clear_sym[0] = spaces[2];
  clear_sym[1] = clear_sym[0] + 22 * size_sym;
}


void Date_window::update(const Coordinates term_siz,const Color_object*wind_c)
{
  window_color[0] = wind_c[0];
  window_color[1] = wind_c[1];
  window_color[2] = wind_c[2];
  if(term_size != term_siz)
  {
    term_size = term_siz;
    update_mode();
    if(correct_size)
    {
      update_position();
    }
  }
  drawing = true;
}

bool Date_window::update_day()
{
  short temp = cur_day();
  return (current_day != temp) ? current_day = temp, true : false;
}

bool Date_window::update_wday()
{
  short temp = cur_wday();
  return (current_wday != temp) ? current_wday = temp, true : false;
}

bool Date_window::update_month()
{
  short temp = cur_month();
  return (current_month != temp) ? current_month = temp, true : false;
}

bool Date_window::update_year()
{
  short temp = cur_year();
  return (current_year != temp) ? current_year = temp, true : false;
}

void Date_window::update_position()
{
  pos_start.reset(term_size.x - window_size[small_mode].x,1);
  if(small_mode)
  {
    pos_back_day.reset(pos_start.x + 1,4);
    pos_back_month.reset(pos_start.x + 1,6);
    pos_back_year.reset(pos_start.x + 1,8);
    
    pos_day.reset(pos_back_day.x + 3,4);
    pos_wday.reset(pos_back_month.x,2);
    pos_month.reset(pos_back_month.x + 3, 6);
    pos_year.reset(pos_back_year.x + 2, 8);
  }
  else
  {
    pos_back_day.reset(pos_start.x + 2,4);
    pos_back_month.reset(pos_start.x + 12,4);
    pos_back_year.reset(pos_start.x + 22,4);
    
    pos_day.reset(pos_back_day.x + 3,5);
    pos_wday.reset(pos_back_month.x,2);
    pos_month.reset(pos_back_month.x + 3, 5);
    pos_year.reset(pos_back_year.x + 2, 5);
  }
}


void Date_window::update_mode()
{
  Coordinates center;
  short radius;
  
  Coordinate_center(center,term_size);
  Calculation_radius(radius,1,center,width);

  short open_space = term_size.x - (center.x + radius * width);
  if(open_space < window_size[1].x)
  {
    correct_size = false;
    small_mode = true;
  }
  else if(open_space < window_size[0].x)
  {
    small_mode = true;
    correct_size = true;
  }
  else
  {
    correct_size = true;
    small_mode = false;
  }
}


void Date_window::draw_day()
{
  if(update_day() || drawing)
  {
    if(small_mode)
    {
      output_object(pos_back_day.x,pos_back_day.y,spaces[1],window_color[1].c);
    }
    else
    {
      for(short i = 0;i < 3; i++)
      {
        output_object(pos_back_day.x,pos_back_day.y + i, spaces[1],window_color[1].c);
      }
    }
    char num_day[10];
    short i = 0;
    move_to_time_format(current_day,num_day,&i);
    num_day[i] = '\0';
    output_object(pos_day.x,pos_day.y,num_day,window_color[1].c);
  }
}


void Date_window::draw_wday()
{
  if(update_wday() || drawing)
  {
    static const char*day_week[7] = {"Monday\0",
                                     "Tuesday\0",
                                     "Wednesday\0",
                                     "Thursday\0",
                                     "Friday\0",
                                     "Saturday\0",
                                     "Sunday\0"};
    
    output_object(pos_wday.x,pos_wday.y,day_week[current_wday - 1],window_color[0].c);
  }
}


void Date_window::draw_month()
{
  if(update_month() || drawing)
  {
    if(small_mode)
    {
      output_object(pos_back_month.x,pos_back_month.y,spaces[1],window_color[1].c);
    }
    else
    {
      for(short i = 0; i < 3; i++)
      {
        output_object(pos_back_month.x,pos_back_month.y + i,spaces[1],window_color[1].c);
      }
    }
    char num_month[10];
    short i = 0;
    move_to_time_format(current_month,num_month,&i);
    num_month[i] = '\0';
    output_object(pos_month.x,pos_month.y,num_month,window_color[1].c);
  }
}


void Date_window::draw_year()
{
  if(update_year() || drawing)
  {
    if(small_mode)
    {
      output_object(pos_back_year.x,pos_back_year.y,spaces[1],window_color[1].c);
    }
    else
    {
      for(short i = 0; i < 3; i++)
      {
        output_object(pos_back_year.x,pos_back_year.y + i,spaces[1],window_color[1].c);
      }
    }
    char num_year[10];
    short i = 0;
    move_to_time_format(current_year,num_year,&i);
    num_year[i] = '\0';
    output_object(pos_year.x,pos_year.y,num_year,window_color[1].c);
  }
}



void Date_window::draw()
{
  if(show_window && correct_size)
  {
    if(drawing)
    {
      for(short i = 0; i < window_size[small_mode].y; i++)
      {
        output_object(pos_start.x,pos_start.y + i,draw_sym[small_mode],window_color[0].c);
      }
    }
    draw_day();
    draw_wday();
    draw_month();
    draw_year();
    drawing = false;
    clearing = true;
  }
}


void Date_window::clear(const bool show_win)
{
  if(show_window != show_win)
  {
    drawing = true;
    show_window = show_win;
  }

  if(!show_window && correct_size && clearing)
  {
    for(short i = 0; i < window_size[small_mode].y; i++)
    {
      output_object(pos_start.x,pos_start.y + i, clear_sym[small_mode],window_color[2].c);
    }
    clearing = false;
  }
}


Date_window::~Date_window()
{
  free(spaces[0]);
  free(spaces[1]);
  free(spaces[2]);
}
