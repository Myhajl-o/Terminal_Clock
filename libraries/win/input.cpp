#include "input.hpp"
#include "Coordinates.hpp"
#include <windows.h>

void block(bool state)
{
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode;
  GetConsoleMode(hStdin, &mode);

  if (state)
  {
    mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
  }
  else
  {
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
  }
  SetConsoleMode(hStdin, mode);
}

void clear_buffer()
{
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  FlushConsoleInputBuffer(hStdin);
}

void get_term_size(Coordinates &size)
{
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hStdout, &csbi);

  size.reset(csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

bool check_buffer(bool &show_date, bool &color)
{
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD events;
  GetNumberOfConsoleInputEvents(hStdin, &events);

  if (events > 0)
  {
    DWORD read_chars;
    INPUT_RECORD ir[4];
    unsigned char c = 1;
    ReadConsoleInput(hStdin, ir, 4, &read_chars);

    for (int i = 0; i < 4; i++)
    {
      if (ir[i].EventType == KEY_EVENT && ir[i].Event.KeyEvent.bKeyDown)
      {
        c = ir[i].Event.KeyEvent.uChar.AsciiChar;
      }
    }

    if (c != 1)
    {
      switch (c)
      {
      case 's':
        show_date = true;
        break;
      case 'w':
        show_date = false;
        break;
      case 'c':
        color = !color;
      }
      clear_buffer();
      return (c == '\n' || c == ' ');
    }
  }
  return false;
}
