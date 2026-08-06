#ifndef PARSING_HPP
#define PARSING_HPP

#include <cstdio>

void skip_to_next_line(FILE*conf_file,char&c);

void move_to_int(short&num,char*symbols,const short size);

bool parsing_conf(short**numbers,char**symbols,const short size_num,const short size_sym);

#endif
