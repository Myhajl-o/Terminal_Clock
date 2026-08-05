#include "background.hpp"
#include "output.hpp"
#include "Color_object.hpp"

// The draw_background function fills the terminal
// window with spaces. It uses the custom data type
// Simple_string for this.
//
// The function returns nothing, but takes the
// terminal size coordinates.
//
// The function is used in the main.cpp file.
void draw_background(const char*symbols,const Color_object colors)
{
  output_symbols(1, 1, symbols, colors);
}
