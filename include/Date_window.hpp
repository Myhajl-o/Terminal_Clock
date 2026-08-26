#ifndef DATE_WINDOW_HPP
#define DATE_WINDOW_HPP

#include "Color_object.hpp"
#include "Coordinates.hpp"

class Date_window
{
  short width;
  Color_object window_back_color;
  Color_object window_front_color;
  Coordinates window_size[2];
  Coordinates term_size;
  short size_sym;
  
  char spaces[145];

  short current_day;
  short current_wday;
  short current_month;
  short current_year;

  bool small_mode;

  Coordinates pos_start;
  Coordinates pos_back_day;
  Coordinates pos_back_month;
  Coordinates pos_back_year;
  Coordinates pos_day;
  Coordinates pos_wday;
  Coordinates pos_month;
  Coordinates pos_year;

  bool update_day();
  bool update_wday();
  bool update_month();
  bool update_year();

  void update_position();
  void update_mode();

  void draw_day();
  void draw_wday();
  void draw_month();
  void draw_year();

  void filling_space(const char*sym);

  public:

  Date_window(const short wi,const Color_object*wind_c,const char*sym);
  void update(const Coordinates term_siz,const Color_object*wind_c);
  void draw();
  void clear();
  ~Date_window();

};


#endif
