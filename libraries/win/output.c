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

short filling_space(char*space,const char*symbol,const short count)
{
  short size_sym = symbol[5];
  short all_size = count * size_sym;
  short i = 0, j = 0;
  for(; i < all_size; i++, j++)
  {
    if(j == size_sym) j = 0 ;
    space[i] = symbol[j];
  }
  space[all_size] = '\0';
  return size_sym;
}

void output_error(const short error)
{
  FILE*err_f = fopen(ERROR_CONF,"w");
  char const*msg_error[11] = {"No errors, everything was read correctly.\n",
                              "Error code : 1\nThe file was either not read or is too small.\n",
                              "Error code : 2\nThe loop successfully read the ‘=’ character,\nbut was unable to find a digit after it\nor encountered an invalid character.\n",
                              "Error code : 3\nAn invalid character was encountered while reading the digits.\n",
                              "Error code : 4\nAfter the digits were read, an invalid character was found.\n",
                              "Error code : 5\nAfter reading the character ‘-’,\nthe quotation mark was not found,\nor an invalid character was read.\n",
                              "Error code : 6\nAn invalid character was read during character reading.\n",
                              "Error code : 7\nNo characters were read during the character read operation.\n",
                              "Error code : 8\nAn invalid character was found after the characters were read.\n",
                              "Error code : 9\nInvalid character in the main loop.\n",
                              "Error code : 10\nInsufficient data to populate the arrays.\n"};
  if(err_f == NULL)return;

  output_symbols(msg_error[error],err_f);

  fclose(err_f);
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
    output_symbols(spaces,stdout);
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
  output_symbols(symbols,stdout);
}

void output_symbols(const char*symbols,FILE*out)
{
  fputs(symbols,out);
  fflush(out);
}


