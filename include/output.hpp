#ifndef OUTPUT_HPP
#define OUTPUT_HPP

void change_color(const bool &color);
void clear_term();
void hide_cursor(bool hide);
void output_symbols(short x, short y, const char *symbols, bool other_color);

#endif
