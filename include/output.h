#ifndef OUTPUT_H
#define OUTPUT_H

#include "Colors.h"

#ifdef __cplusplus
extern "C"
{
#endif

void clear_term();
void full_clear_term(const short y,const char*spaces);
void hide_cursor(char hide);
void set_cursor(short x,short y);
void output_symbols(short x, short y, const char *symbols,const Colors color);
void output_message(const char*msg);
void output_number(const short num);

#ifdef __cplusplus
}
#endif

#endif
