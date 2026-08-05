#include "Settings_clock.hpp"
#include "Color_object.hpp"

Settings_clock::Settings_clock()
{
  i_color = 0;
  size_num = 17;
  size_sym = 18;

  array_num[0] = &width;
  array_num[1] = &main_back_color[0];
  array_num[2] = &main_back_color[1];
  array_num[3] = &main_front_color[0];
  array_num[4] = &main_front_color[1];
  array_num[5] = &circle_back_color[0];
  array_num[6] = &circle_back_color[1];
  array_num[7] = &circle_front_color[0];
  array_num[8] = &circle_front_color[1];
  array_num[9] = &number_back_color[0];
  array_num[10] = &number_back_color[1];
  array_num[11] = &number_front_color[0];
  array_num[12] = &number_front_color[1];
  array_num[13] = &second_back_color[0];
  array_num[14] = &second_back_color[1];
  array_num[15] = &second_front_color[0];
  array_num[16] = &second_front_color[1];

  for(short i = 0; i < size_num; i++)
  {
    *(array_num[i]) = 0;
  }

  array_sym[0] = circle_symbol;
  array_sym[1] = tick_number;
  array_sym[2] = first_number;
  array_sym[3] = second_number;
  array_sym[4] = third_number;
  array_sym[5] = fourth_number;
  array_sym[6] = fifth_number;
  array_sym[7] = sixth_number;
  array_sym[8] = seventh_number;
  array_sym[9] = eighth_number;
  array_sym[10] = ninth_number;
  array_sym[11] = tenth_number;
  array_sym[12] = eleventh_number;
  array_sym[13] = twelfth_number;
  array_sym[14] = second_vertical_line;
  array_sym[15] = second_diagonal1_line;
  array_sym[16] = second_diagonal2_line;
  array_sym[17] = second_horizontal_line;

  for(int i = 0; i < 13; i++)
  {
    num_clock_symbol[i] = array_sym[i + 1];
  }
  for(int i = 0; i < 4; i++)
  {
    second_symbol[i] = array_sym[i + 14];
  }
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

  circle_back_color[0] = black_back;
  circle_back_color[1] = white_back;
  circle_front_color[0] = black_front;
  circle_front_color[1] = white_front;
  circle_symbol[0] = ' ';

  number_back_color[0] = white_back;
  number_back_color[1] = black_back;
  number_front_color[0] = black_front;
  number_front_color[1] = white_front;

  tick_number[0] = '.';
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
    short add = (i >= 11 && i <= 13);
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
    if(*(array_num[i]) < 30 || (*(array_num[i]) > 37 && *(array_num[i]) < 40) || (*(array_num[i]) > 47 && *(array_num[i]) < 90) || (*(array_num[i]) > 97 && *(array_num[i]) < 100) || *(array_num[i]) > 107)
    {
      return false;
    }
  }
  return true;
}

void Settings_clock::new_settings()
{
  if(!validation_check())
  {
    default_settings();
  }
}

short Settings_clock::get_width()
{
  return width;
}

Color_object Settings_clock::get_background_color(const bool color)
{
  return Color_object(main_back_color[color],main_front_color[color],main_back_color[color],main_front_color[color]);
}

Color_object Settings_clock::get_circle_color(const bool color)
{
  return Color_object(circle_back_color[color],circle_front_color[color],main_back_color[color],main_front_color[color]);
}

Color_object Settings_clock::get_number_color(const bool color)
{
  return Color_object(number_back_color[color],number_front_color[color],main_back_color[color],main_front_color[color]);
}

Color_object Settings_clock::get_second_color(const bool color)
{
  return Color_object(second_back_color[color],second_front_color[color],main_back_color[color],main_front_color[color]);
}

char Settings_clock::get_circle_symbol()
{
  return circle_symbol[0];
}

char** Settings_clock::get_num_clock_symbols()
{
  return num_clock_symbol;
}

char** Settings_clock::get_second_symbols()
{
  return second_symbol;
}

Settings_clock::~Settings_clock()
{

}
