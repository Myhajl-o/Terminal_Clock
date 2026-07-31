#include "background.hpp"
#include "Coordinates.hpp"
#include "Simple_string.hpp"
#include "output.hpp"

void draw_background(const Coordinates &size)
{
  Simple_string canvas((unsigned int)(size.x * size.y));
  output_symbols(1, 1, canvas.symbols, false);
}
