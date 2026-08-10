#include "background.hpp"
#include "output.h"
#include "Color_object.hpp"

// The draw_background function fills the terminal
// window with spaces.
// 
// The function is used in the main.cpp file.
void draw_background(const char*symbols,const Color_object colors)
{
  output_symbols(0, 1, symbols, colors.c);
}
