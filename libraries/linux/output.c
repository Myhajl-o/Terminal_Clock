#include "output.h"
#include "Colors.h"
#include <stdio.h>

void move_to_char(short num, char*msg,short*i_msg)
{
  char s[6];
  short i = 5;
  short j = 0;
  char sub = 0;
  if(num < 0)
  {
    sub = !sub;
    num = -num;
  }
  if(!num)
  {
    s[i--] = '0';
  }
  else
  {
    for(;num;num/=10)s[i--] = num%10 + '0';
  }
  if(sub)s[i--] = '-';
  for(; j < (5 - i); j++)msg[(*i_msg)++] = s[i + j + 1];
}

void move_to_time_format(short num, char*msg,short*i_msg)
{
  char s[7];
  short i = 6;
  short j = 0;
  char zero = 0;
  char sub = 0;
  if(num < 0)
  {
    sub = !sub;
    num = -num;
  }
  if(!num)
  {
    s[i--] = '0';
    zero = !zero;
  }
  else
  {
    for(;num;num/=10,zero = !zero)s[i--] = num%10 + '0';
  }
  if(zero)s[i--] = '0';
  if(sub)s[i--] = '-';
  for(; j < (6 - i); j++)msg[(*i_msg)++] = s[i + j + 1];
}

void clear_term()
{
  static const char*esc_clear = "\033[0m\0";
  output_symbols(esc_clear);
}

/* The clear_term function resets all escape codes
 * that were previously output, clears the terminal
 * of characters, and moves the cursor to the beginning
 * of the terminal, using escape codes.
 *
 * The function is used in the main.cpp file. */
void full_clear_term(const short y,const char*spaces)
{
  short i = 1;
  clear_term();
  for(;i <= y; i++)
  {
    set_cursor(0,i);
    output_symbols(spaces);
  }
  set_cursor(0,1);
}

/* The hide_cursor function hides the terminal cursor
 * using escape codes.
 *
 * The function is used in the main.cpp file. */
void hide_cursor(const char hide)
{
  static char esc_cursor[8] = "\033[?25l\0";
  if (hide)
  {
    esc_cursor[5] = 'l';
  }
  else
  {
    esc_cursor[5] = 'h';
  }
  output_symbols(esc_cursor);
}

void set_cursor(const short x,const short y)
{
  char esc_pos[20] = "\033[";
  short i = 2;
  move_to_char(y,esc_pos,&i);
  esc_pos[i++] = ';';
  move_to_char(x,esc_pos,&i);
  esc_pos[i++] = 'H';esc_pos[i] = '\0';
  output_symbols(esc_pos);
}

void set_color(const Colors color)
{
  char esc_color[20] = "\033[";
  short i = 2;
  move_to_char(color.back,esc_color,&i);
  esc_color[i++] = ';';
  move_to_char(color.front,esc_color,&i);
  esc_color[i++] = 'm';esc_color[i] = '\0';
  output_symbols(esc_color);
}

/* The output_symbols function is written in C. It is the primary
 * output function for this utility. The function prints elements from
 * a char array to specific terminal locations using specific colors.
 *
 * It is used in the following files: main.cpp, background.cpp, watch_face.cpp, and Second-hand.cpp. */
void output_object(const short x,const short y, const char *symbols,const Colors color)
{
  set_cursor(x,y);
  set_color(color);
  output_symbols(symbols);
}

void output_symbols(const char*symbols)
{
  fputs(symbols,stdout);
  fflush(stdout);
}


