#ifndef OUTPUT_H
#define OUTPUT_H

#include "Colors.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

void move_to_char(short num, char*msg,short*i_msg);
void move_to_time_format(short num, char*msg,short*i_msg);
void output_error(const short error);
void clear_term();
void full_clear_term(const short y,const char*spaces);
void hide_cursor(const char hide);
void set_cursor(const short x,const short y);
void set_color(const Colors color);
void output_object(const short x,const short y, const char *symbols,const Colors color);
void output_symbols(const char*symbols,FILE*out);

#ifdef __cplusplus
}
#endif

#endif
