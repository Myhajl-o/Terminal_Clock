#ifndef PARSING_HPP
#define PARSING_HPP

void skip_to_next_line(char*buffer,short&i_buf,const short&all_size);

void move_to_int(short&num,char*symbols,const short size);

bool parsing_conf(short**numbers,char**symbols,const short size_num,const short size_sym);

#endif
