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

// The clear_term function resets all escape codes
// that were previously output, clears the terminal
// of characters, and moves the cursor to the beginning
// of the terminal, using escape codes.
//
// The function takes no arguments and returns nothing.
//
// The function is used in the main.cpp file.
void clear_term()
{
  printf("\033[0m\033[2J\033[1;1H");
}

// The hide_cursor function hides the terminal cursor
// using escape codes.
//
// The function returns nothing but takes a bool value.
//
// The function is used in the main.cpp file.
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
