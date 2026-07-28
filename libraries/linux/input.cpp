#include "input.hpp"
#include "Coordinates.hpp"
#include <sys/ioctl.h>
#include <termios.h>
#include <uchar.h>
#include <unistd.h>

void clear_buffer() { tcflush(STDIN_FILENO, TCIFLUSH); }

void block(bool enable)
{
  static struct termios oldt, newt;
  static bool initialized = false;
  if (!initialized)
  {
    if (tcgetattr(STDIN_FILENO, &oldt) < 0)
    {
      return;
    }
    initialized = true;
  }

  if (enable)
  {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  }
  else
  {
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  }
}

void get_term_size(Coordinates &size)
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  size.reset(w.ws_col, w.ws_row);
}

bool check_buffer(bool &show_date, bool &color)
{
  char32_t bytes;
  char c = '1';
  ioctl(STDIN_FILENO, FIONREAD, &bytes);
  if (bytes > 0)
  {
    read(STDIN_FILENO, &c, 1);

    switch (c)
    {
    case '\x1b':
      char seq[3];
      if (read(STDIN_FILENO, &seq[0], 1) == 1 &&
          read(STDIN_FILENO, &seq[1], 1) == 1)
      {
        if (seq[0] == '[')
        {
          if (seq[1] == 'B')
          {
            show_date = true;
          }
          else if (seq[1] == 'A')
          {
            show_date = false;
          }
        }
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
