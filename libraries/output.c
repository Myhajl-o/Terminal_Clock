#include "output.h"
#include "Colors.h"
#include <stdio.h>


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
void hide_cursor(char hide)
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

void output_symbols(short x, short y, const char *symbols,const Colors color)
{
  printf("\033[%dm\033[%dm\033[%d;%dH%s\033[%dm\033[%dm", color.back,color.front, y, x, symbols,color.main_back,color.main_front);

  fflush(stdout);
}
