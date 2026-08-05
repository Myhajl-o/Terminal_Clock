#include "output.hpp"
#include "Color_object.hpp"
#include <cstdio>


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

void output_symbols(short x, short y, const char *symbols,Color_object obj)
{
  printf("\033[%dm\033[%dm\033[%d;%dH%s\033[%dm\033[%dm", obj.back_color,obj.front_color, y, x, symbols,obj.main_back_color,obj.main_front_color);

  fflush(stdout);
}
