#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

void skip_to_next_line(char*buffer,size_t*i_buf,const size_t all_size);
void move_to_int(short*num,char*symbols,const short size);
char parsing_conf(short**numbers,char**symbols,const short size_num,const short size_sym);
char parsing_main(short *flag,const char* const*argv);

#ifdef __cplusplus
}
#endif

#endif
