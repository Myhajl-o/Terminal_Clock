#ifndef OUTPUT_H
#define OUTPUT_H

#include "Colors.h"

#ifdef __cplusplus
extern "C"
{
#endif

void clear_term(const char*spaces);
void hide_cursor(char hide);
void output_symbols(short x, short y, const char *symbols,const Colors color);

#ifdef __cplusplus
}
#endif

#endif
