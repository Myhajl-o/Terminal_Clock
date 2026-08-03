#include "background.hpp"
#include "output.hpp"

// The draw_background function fills the terminal
// window with spaces. It uses the custom data type
// Simple_string for this.
//
// The function returns nothing, but takes the
// terminal size coordinates.
//
// The function is used in the main.cpp file.
void draw_background(const char*symbols)
{
  output_symbols(1, 1, symbols, false);
}
