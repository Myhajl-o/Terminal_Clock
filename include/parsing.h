#ifndef PARSING_H
#define PARSING_H


#ifdef __cplusplus
extern "C"
{
#endif

void skip_to_next_line(char*buffer,int*i_buf,const int all_size);
void skip_comment(char*buffer,int*i_buf,const int all_size);
char transfer_to_the(char c,char*buffer,int*i_buf,const int all_size);
char transfer_to_number(char*buffer,int*i_buf,const int all_size);
void move_to_int(short*num,char*symbols,const short size);
short check_size_symbol(const char c);
char parsing_conf(short**numbers,char**symbols,const short size_num,const short size_sym,short*error);
char comparisons(const char*arg1,const char*arg2);
char parsing_main(short *flag,const char* const*argv);

#ifdef __cplusplus
}
#endif

#endif
