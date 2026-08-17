#include "background.hpp"
#include "output.h"
#include "Color_object.hpp"

// The draw_background function fills the terminal
// window with spaces.
// 
// The function is used in the main.cpp file.
void draw_background(const short y,const char*symbols,const Color_object colors)
{
  for(short i = 1; i <= y; i++)
  {
    output_symbols(0, i, symbols, colors.c);
  }
}
