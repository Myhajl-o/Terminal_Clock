#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "Color_object.hpp"

void clear_term();
void hide_cursor(bool hide);
void output_symbols(short x, short y, const char *symbols, Color_object color);

#endif
