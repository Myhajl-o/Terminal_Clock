#include "output.hpp"
#include <cstdio>
#include <cstdlib>

short main_color;
short secondary_color;
short symbol_color;

void change_color(const bool &color)
{
  if (color)
  {
    main_color = 40;
    secondary_color = 47;
    symbol_color = 37;
  }
  else
  {
    main_color = 47;
    secondary_color = 40;
    symbol_color = 30;
  }
  printf("\033[%dm\033[%dm", main_color, symbol_color);
}

void clear()
{
  printf("\033[0m");
  std::system("clear");
}

void cursor(bool hide)
{
  if (hide)
  {
    printf("\033[?25l");
  }
  else
  {
    printf("\033[?25h");
  }
}

void output_symbols(short x, short y, const char *s, bool other_color)
{
  if (other_color)
  {
    printf("\033[%dm\033[%d;%dH%s\033[%dm", secondary_color, y, x, s,
           main_color);
  }
  else
  {
    printf("\033[%d;%dH%s", y, x, s);
  }
  fflush(stdout);
}
