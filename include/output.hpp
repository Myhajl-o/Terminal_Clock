#pragma once

void change_color(const bool &color);
void clear_term();
void hide_cursor(bool hide);
void output_symbols(short x, short y, const char *symbols, bool other_color);
