#include "input.hpp"
#include "Coordinates.hpp"
#include <windows.h>

void setting_term_mode(bool raw_term)
{
  //==== block input =====================
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode;
  DWORD inMode;
  GetConsoleMode(hStdin, &mode);

  if (raw_term)
  {
    mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
  }
  else
  {
    mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
  }
  SetConsoleMode(hStdin, mode);

  //==== Off quick edit mode ==============
  GetConsoleMode(hStdin, &inMode);
  if (raw_term)
  {
    inMode &= ~ENABLE_QUICK_EDIT_MODE;
    inMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
  }
  else
  {
    inMode |= ENABLE_QUICK_EDIT_MODE;
    inMode |= ENABLE_EXTENDED_FLAGS;
  }
  SetConsoleMode(hStdin, inMode);

  //==== read escape code =================
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD outMode = 0;
  GetConsoleMode(hOut, &outMode);
  outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, outMode);
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
    INPUT_RECORD ir;
    ReadConsoleInput(hStdin, &ir, 1, &read_chars);

    if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown)
    {
      if (ir.Event.KeyEvent.wVirtualKeyCode == VK_SPACE || ir.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
      {
        return true;
      }
      else if (ir.Event.KeyEvent.wVirtualKeyCode == VK_DOWN || ir.Event.KeyEvent.wVirtualKeyCode == 'S')
      {
        show_date = true;
      }
      else if (ir.Event.KeyEvent.wVirtualKeyCode == VK_UP || ir.Event.KeyEvent.wVirtualKeyCode == 'W')
      {
        show_date = false;
      }
      else if (ir.Event.KeyEvent.wVirtualKeyCode == 'C')
      {
        color = !color;
      }
    }
  }
  return false;
}
