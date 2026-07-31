#include "output.hpp"
#include <cstdio>

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

void clear_term()
{
  printf("\033[0m\033[2J");
}

void hide_cursor(bool hide)
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

void output_symbols(short x, short y, const char *symbols, bool other_color)
{
  if (other_color)
  {
    printf("\033[%dm\033[%d;%dH%s\033[%dm", secondary_color, y, x, symbols,
           main_color);
  }
  else
  {
    printf("\033[%d;%dH%s", y, x, symbols);
  }
  fflush(stdout);
}
