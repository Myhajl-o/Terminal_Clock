#include "Date_window.hpp"
#include "Coordinates.hpp"
#include "Color_object.hpp"
#include "math.hpp"
#include "timedate.hpp"
#include "output.h"


Date_window::Date_window(const short wi,const Color_object*wind_c,const char*sym)
{
  window_size[0].reset(32,8);
  window_size[1].reset(10,9);
  term_size.reset(0,0);
  current_day = 32;
  current_wday = 7;
  current_month = 13;
  current_year = 2077;
  width = wi;
  window_back_color = wind_c[0];
  window_front_color = wind_c[1];
  filling_space(sym);
}


void Date_window::filling_space(const char*sym)
{
  size_sym = sym[5];
  short all_size = window_size[0].x * size_sym;
  for(short i = 0,j = 0; i < all_size; i++, j++)
  {
    if(j == size_sym) j = 0 ;
    spaces[i] = sym[j];
  }
  spaces[all_size] = '\0';
}


void Date_window::update(const Coordinates term_siz,const Color_object*wind_c)
{
  window_back_color = wind_c[0];
  window_front_color = wind_c[1];
  if(term_size != term_siz)
  {
    update_mode();
    update_position();
  }
  term_size = term_siz;
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

// need a rework
void Date_window::update_position()
{
  pos_start.reset(term_size.x - window_size[small_mode].x,1);
  short shift[2][3] = {{4,6,8},{5,5,5}};
  if(small_mode)
  {
    pos_back_day.reset(pos_start.x + 1,shift[small_mode][0]);
    pos_back_month.reset(pos_start.x + 1,shift[small_mode][1]);
    pos_back_year.reset(pos_start.x + 1,shift[small_mode][2]);
  }
  else
  {
    pos_back_day.reset(pos_start.x + 2,4);
    pos_back_month.reset(pos_start.x + 12,4);
    pos_back_year.reset(pos_start.x + 22,4);
  }
  pos_day.reset(pos_back_day.x + 3,shift[small_mode][0]);
  pos_month.reset(pos_back_month.x + 3, shift[small_mode][1]);
  pos_back_year.reset(pos_back_year.x + 2, shift[small_mode][2]);
}


void Date_window::update_mode()
{
  Coordinates center;
  short radius;
  
  Coordinate_center(center,term_size);
  Calculation_radius(radius,1,center,width);

  short open_space = term_size.x - (center.x + radius * width);
  if(open_space < window_size[0].x)
  {
    small_mode = true;
  }
}
