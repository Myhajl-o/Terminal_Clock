#include "output.h"
#include "Colors.h"
#include <stdio.h>
#include <windows.h>


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
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hStdout, 7);
}

/* The clear_term function resets all escape codes
 * that were previously output, clears the terminal
 * of characters, and moves the cursor to the beginning
 * of the terminal, using escape codes.
 *
 * The function is used in the main.cpp file. */
void full_clear_term(const short y,const char*spaces)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;

  SetConsoleTextAttribute(hStdout, 7);
  pos.X = 0;
  pos.Y = 1;

  for(; pos.Y <= y ; pos.Y++)
  {
    SetConsoleCursorPosition(hStdout, pos);
    output_symbols(spaces);
  }

  pos.Y = 1;
  SetConsoleCursorPosition(hStdout, pos);
}

/* The hide_cursor function hides the terminal cursor
 * using escape codes.
 *
 * The function is used in the main.cpp file. */
void hide_cursor(const char hide)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;

  GetConsoleCursorInfo(hStdout, &cursorInfo);
  cursorInfo.bVisible = !hide;
  SetConsoleCursorInfo(hStdout, &cursorInfo);
}

void set_cursor(const short x,const short y)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X = x;
  pos.Y = y;

  SetConsoleCursorPosition(hStdout, pos);
}

void set_color(const Colors color)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

  unsigned short background = (color.back < 50) ? (color.back%10) : (color.back%10) + 8;
  unsigned short foreground = (color.front < 50) ? (color.front%10) : (color.front%10) + 8;
  unsigned short atribute = (background << 4) | foreground;

  SetConsoleTextAttribute(hStdout, atribute);
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


