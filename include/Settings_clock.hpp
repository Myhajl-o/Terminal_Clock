#ifndef SETTINGS_CLOCK_HPP
#define SETTINGS_CLOCK_HPP

#include "Color_object.hpp"

class Settings_clock
{
  private:

  const short size_num;
  const short size_sym;

  short width;

  short main_back_color[2];
  short main_front_color[2];
  char bg_symbol[10];

  short circle_back_color[2];
  short circle_front_color[2];
  char circle_symbol[10];

  short tick_back_color[2];
  short tick_front_color[2];
  char tick_symbol[10];

  short number_back_color[2];
  short number_front_color[2];
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
  short number_shift[12];

  short second_back_color[2];
  short second_front_color[2];
  char second_vertical_line[10];
  char second_diagonal1_line[10];
  char second_diagonal2_line[10];
  char second_horizontal_line[10];

  short minute_back_color[2];
  short minute_front_color[2];
  char minute_vertical_line[10];
  char minute_diagonal1_line[10];
  char minute_diagonal2_line[10];
  char minute_horizontal_line[10];

  short error;

  short*array_num[37];
  char*array_sym[23];

  Color_object bg_color[2];
  Color_object wf_colors[2][3];
  Color_object sec_color[2];
  Color_object min_color[2];

  char*num_clock_symbol[13];
  char*second_symbol[5];
  char*minute_symbol[5];


  void initialization();
  void default_settings();
  bool validation_check();
  void new_settings(const bool conf);

  public:

  Settings_clock();

  short get_width();
  const short* get_num_shift();
  const Color_object get_bg_color(const bool color);
  const Color_object*get_wf_color(const bool color);
  const Color_object get_sec_color(const bool color);
  const Color_object get_min_color(const bool color);
  const char* get_bg_symbol();
  const char* get_circ_symbol();
  const char* const* get_num_symbols();
  const char* const* get_sec_symbols();
  const char* const* get_min_symbols();

  ~Settings_clock();
};

#endif
