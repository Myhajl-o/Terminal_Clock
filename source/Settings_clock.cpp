#include "Settings_clock.hpp"
#include "Color_object.hpp"
#include "parsing.h"
#include "output.h"

void Settings_clock::initialization()
{
  array_num[0] = &width;
  array_num[1] = &main_back_color[0];
  array_num[2] = &main_back_color[1];
  array_num[3] = &main_front_color[0];
  array_num[4] = &main_front_color[1];
  array_num[5] = &circle_back_color[0];
  array_num[6] = &circle_back_color[1];
  array_num[7] = &circle_front_color[0];
  array_num[8] = &circle_front_color[1];
  array_num[9] = &tick_back_color[0];
  array_num[10] = &tick_back_color[1];
  array_num[11] = &tick_front_color[0];
  array_num[12] = &tick_front_color[1];
  array_num[13] = &number_back_color[0];
  array_num[14] = &number_back_color[1];
  array_num[15] = &number_front_color[0];
  array_num[16] = &number_front_color[1];
  for(int i = 0; i < 12; i++)
  {
    array_num[17 + i] = &number_shift[i];
  }

  array_num[29] = &second_back_color[0];
  array_num[30] = &second_back_color[1];
  array_num[31] = &second_front_color[0];
  array_num[32] = &second_front_color[1];

  for(short i = 0; i < size_num; i++)
  {
    *(array_num[i]) = 0;
  }

  array_sym[0] = bg_symbol;
  array_sym[1] = circle_symbol;
  array_sym[2] = tick_symbol;
  array_sym[3] = first_number;
  array_sym[4] = second_number;
  array_sym[5] = third_number;
  array_sym[6] = fourth_number;
  array_sym[7] = fifth_number;
  array_sym[8] = sixth_number;
  array_sym[9] = seventh_number;
  array_sym[10] = eighth_number;
  array_sym[11] = ninth_number;
  array_sym[12] = tenth_number;
  array_sym[13] = eleventh_number;
  array_sym[14] = twelfth_number;
  array_sym[15] = second_vertical_line;
  array_sym[16] = second_diagonal1_line;
  array_sym[17] = second_diagonal2_line;
  array_sym[18] = second_horizontal_line;

  for(int i = 0; i < 13; i++)
  {
    num_clock_symbol[i] = array_sym[i + 2];
  }
  for(int i = 0; i < 4; i++)
  {
    second_symbol[i] = array_sym[i + 15];
  }
  second_symbol[4] = array_sym[0];
}

Settings_clock::Settings_clock():size_num(33),size_sym(19)
{
  initialization();
  new_settings(parsing_conf(array_num,array_sym,size_num,size_sym,&error));
  output_error(error);
}


void Settings_clock::default_settings()
{
  const short black_back = 40;
  const short black_front = 30;
  const short white_back = 47;
  const short white_front = 37;

  width = 2;
  main_back_color[0] = white_back;
  main_back_color[1] = black_back;
  main_front_color[0] = white_front;
  main_front_color[1] = black_front;
  bg_symbol[0] = ' ';
  bg_symbol[5] = 1;

  circle_back_color[0] = black_back;
  circle_back_color[1] = white_back;
  circle_front_color[0] = black_front;
  circle_front_color[1] = white_front;
  circle_symbol[0] = ' ';
  circle_symbol[5] = 1;

  tick_back_color[0] = white_back;
  tick_back_color[1] = black_back;
  tick_front_color[0] = black_front;
  tick_front_color[1] = white_front;
  tick_symbol[0] = '.';

  number_back_color[0] = white_back;
  number_back_color[1] = black_back;
  number_front_color[0] = black_front;
  number_front_color[1] = white_front;

  first_number[0] = '1';
  second_number[0] = '2';
  third_number[0] = '3';
  fourth_number[0] = '4';
  fifth_number[0] = '5';
  sixth_number[0] = '6';
  seventh_number[0] = '7';
  eighth_number[0] = '8';
  ninth_number[0] = '9';
  tenth_number[0] = '1';
  tenth_number[1] = '0';
  eleventh_number[0] = '1';
  eleventh_number[1] = '1';
  twelfth_number[0] = '1';
  twelfth_number[1] = '2';

  for(int i = 0; i < 11; i++)
  {
    number_shift[i] = 2;
  }
  number_shift[11] = 1;

  second_back_color[0] = white_back;
  second_back_color[1] = black_back;
  second_front_color[0] = black_front;
  second_front_color[1] = white_front;

  second_vertical_line[0] = '|';
  second_diagonal1_line[0] = '/';
  second_diagonal2_line[0] = '\\';
  second_horizontal_line[0] = '-';

  for(short i = 0; i < size_sym; i++ )
  {
    short add = (i >= 12 && i <= 14);
    array_sym[i][1+add] = '\0';
  }
}

bool Settings_clock::validation_check()
{
  if(*(array_num[0]) < 1 || *(array_num[0]) > 4)
  {
    return false;
  }
  
  for(int i = 1; i < size_num; i++)
  {
    i += (i == 17) ? 12 : 0;
    if(*(array_num[i]) < 30 || (*(array_num[i]) > 37 && *(array_num[i]) < 40) || (*(array_num[i]) > 47 && *(array_num[i]) < 90) || (*(array_num[i]) > 97 && *(array_num[i]) < 100) || *(array_num[i]) > 107)
    {
      return false;
    }
  }
  
  for(int i = 0; i < 12; i++)
  {
    if(number_shift[i] < 0 || number_shift[i] > 4)
    {
      return false;
    }
  }

  return true;
}

void Settings_clock::new_settings(const bool conf)
{
  if(conf && validation_check())
  {
    short temp = check_size_symbol(bg_symbol[0]);
    bg_symbol[temp] = '\0';
    bg_symbol[5] = temp;

    temp = check_size_symbol(circle_symbol[0]);
    circle_symbol[temp] = '\0';
    circle_symbol[5] = temp;
  }
  else
  {
    default_settings();
  }
  bg_color[0].reset(main_back_color[0],main_front_color[0]);
  bg_color[1].reset(main_back_color[1],main_front_color[1]);

  wf_colors[0][0].reset(circle_back_color[0],circle_front_color[0]);
  wf_colors[0][1].reset(tick_back_color[0],tick_front_color[0]);
  wf_colors[0][2].reset(number_back_color[0],number_front_color[0]);

  wf_colors[1][0].reset(circle_back_color[1],circle_front_color[1]);
  wf_colors[1][1].reset(tick_back_color[1],tick_front_color[1]);
  wf_colors[1][2].reset(number_back_color[1],number_front_color[1]);

  sec_color[0].reset(second_back_color[0],second_front_color[0]);
  sec_color[1].reset(second_back_color[1],second_front_color[1]);
}


short Settings_clock::get_width()
{
  return width;
}

const short* Settings_clock::get_num_shift()
{
  return number_shift;
}

const Color_object Settings_clock::get_bg_color(const bool color)
{
  return bg_color[color];
}

const Color_object*Settings_clock::get_wf_color(const bool color)
{
  return wf_colors[color];
}

const Color_object Settings_clock::get_sec_color(const bool color)
{
  return sec_color[color];
}

const char* Settings_clock::get_bg_symbol()
{
  return bg_symbol;
}

const char* Settings_clock::get_circ_symbol()
{
  return circle_symbol;
}

const char* const* Settings_clock::get_num_symbols()
{
  return num_clock_symbol;
}

const char* const* Settings_clock::get_sec_symbols()
{
  return second_symbol;
}

Settings_clock::~Settings_clock()
{

}
