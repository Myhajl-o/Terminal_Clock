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
  HANDLE hStdin = GetStdHandle(STD_IINPUT_HANDLE);
  FlushConsoleInputBuffer(hStdin);
}

void get_term_size(Coordinates &size)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hStdout, &csbi);

  size.reset(csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

bool check_buffer(bool &show_date, bool &color)
{
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD events;
  unsigned char c = 1;
  GetNumberOfConsoleInputEvents(hStdin, &events);

  if (events > 0)
  {
    DWORD read_chars;
    ReadConsoleA(hStdin, &c, 1, &read_chars, NULL);

    switch (c)
    {
    case 0:
    case 224:
      ReadConsoleA(hStdin, &c, 1, &read_chars, NULL);
      if (c == 80)
      {
        show_date = true;
      }
      else if (c == 72)
      {
        show_date = false;
      }
      break;
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
  }
  return (c == '\n' || c == ' ');
}
