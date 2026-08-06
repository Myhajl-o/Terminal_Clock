#ifndef SETTINGS_CLOCK_HPP
#define SETTINGS_CLOCK_HPP

#include "Color_object.hpp"

class Settings_clock
{
  private:

  short i_color;

  short size_num;
  short size_sym;

  short width;

  short main_back_color[2];
  short main_front_color[2];

  short circle_back_color[2];
  short circle_front_color[2];
  char circle_symbol[10];

  short number_back_color[2];
  short number_front_color[2];
  char tick_number[10];
  char first_number[10];
  char second_number[10];
  char third_number[10];
  char fourth_number[10];
  char fifth_number[10];
  char sixth_number[10];
  char seventh_number[10];
  char eighth_number[10];
  char ninth_number[10];
  char tenth_number[10];
  char eleventh_number[10];
  char twelfth_number[10];

  short second_back_color[2];
  short second_front_color[2];
  char second_vertical_line[10];
  char second_diagonal1_line[10];
  char second_diagonal2_line[10];
  char second_horizontal_line[10];

  short*array_num[17];
  char*array_sym[18];

  char*num_clock_symbol[13];
  char*second_symbol[4];

  public:

  Settings_clock();

  void default_settings();

  bool validation_check();

  void new_settings();

  short get_width();

  Color_object get_background_color(const bool color);

  Color_object get_circle_color(const bool color);

  Color_object get_number_color(const bool color);

  Color_object get_second_color(const bool color);

  char get_circle_symbol();

  char** get_num_clock_symbols();

  char** get_second_symbols();

  ~Settings_clock();
};

#endif
