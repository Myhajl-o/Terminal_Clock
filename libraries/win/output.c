#include "output.h"
#include "Colors.h"
#include <stdio.h>
#include <windows.h>

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
  short i = 1;
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;

  SetConsoleTextAttribute(hStdout, 7);
  pos.X = 0;
  pos.Y = 1;

  for(; pos.Y <= y ; pos.Y++)
  {
    SetConsoleCursorPosition(hStdout, pos);
    printf("%s",spaces);
  }

  pos.Y = 1;
  SetConsoleCursorPosition(hStdout, pos);
}

/* The hide_cursor function hides the terminal cursor
 * using escape codes.
 *
 * The function is used in the main.cpp file. */
void hide_cursor(char hide)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;

  GetConsoleCursorInfo(hStdout, &cursorInfo);
  cursorInfo.bVisible = !hide;
  SetConsoleCursorInfo(hStdout, &cursorInfo);
}
/* The output_symbols function is written in C. It is the primary
 * output function for this utility. The function prints elements from
 * a char array to specific terminal locations using specific colors.
 *
 * It is used in the following files: main.cpp, background.cpp, watch_face.cpp, and Second-hand.cpp. */
void output_symbols(short x, short y, const char *symbols,const Colors color)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

  unsigned short background = (color.back < 50) ? (color.back%10) : (color.back%10) + 8;
  unsigned short foreground = (color.front < 50) ? (color.front%10) : (color.front%10) + 8;

  unsigned short atribute = (background << 4) | foreground;

  COORD pos;

  SetConsoleTextAttribute(hStdout, atribute);

  pos.X = x;
  pos.Y = y;

  SetConsoleCursorPosition(hStdout, pos);

  printf("%s", symbols);

  fflush(stdout);
}

void output_message(const char*msg)
{
  printf("%s",msg);
}


void set_cursor(short x,short y)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;

  pos.X = x;
  pos.Y = y;

  SetConsoleCursorPosition(hStdout, pos);
}
