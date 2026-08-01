#include "background.hpp"
#include "Coordinates.hpp"
#include "Simple_string.hpp"
#include "output.hpp"

// The draw_background function fills the terminal
// window with spaces. It uses the custom data type
// Simple_string for this.
//
// The function returns nothing, but takes the
// terminal size coordinates.
//
// The function is used in the main.cpp file.
void draw_background(const Coordinates &size)
{
  Simple_string canvas((unsigned int)(size.x * size.y));
  output_symbols(1, 1, canvas.symbols, false);
}
