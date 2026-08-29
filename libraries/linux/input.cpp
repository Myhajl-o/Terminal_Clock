/* The input library contains functions for configuring the terminal and a function for
 * reading input. I may improve it in the future, but for now it has three main
 * functions, and I don't have anything else to say about it.
 *
 * The input library is used in the file heart_clock.cpp.*/




#include "input.hpp"
#include "Coordinates.hpp"
#include <sys/ioctl.h>
#include <termios.h>
#include <uchar.h>
#include <unistd.h>

// The clear_buffer function clears the entire internal buffer
// of the terminal from input.
//
// The function is used in the check_buffer function.
void clear_buffer() { tcflush(STDIN_FILENO, TCIFLUSH); }

// The setting_term_mode function switches the terminal
// into raw mode and vice versa. In this mode, the terminal
// does not display user input, but simply stores it in
// its internal buffer.
//
// The function is used in the heart_clock.cpp file.
void setting_term_mode(bool raw_term)
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

  if (raw_term)
  {
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  }
  else
  {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  }
}

// The get_term_size function writes the total number of
// characters that can fit along the x and y axes into the size variable.
//
// The function is used in the heart_clock.cpp file.
void get_term_size(Coordinates &size)
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  size.reset(w.ws_col, w.ws_row);
}

// The check_buffer function reads the internal buffer
// of the terminal and clears it. The function is used
// to change the state of a bool variable and close the program.
//
// The function is used in the heart_clock.cpp file.
bool check_buffer(bool &show_date, bool &color)
{
  char32_t bytes;
  unsigned char c = 1;
  ioctl(STDIN_FILENO, FIONREAD, &bytes);
  if (bytes > 0)
  {
    read(STDIN_FILENO, &c, 1);

    switch (c)
    {
    case '\033':
      ioctl(STDIN_FILENO, FIONREAD, &bytes);
      if (bytes >= 2)
      {
        char seq[3];
        read(STDIN_FILENO, seq, 2);

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
      else if (bytes == 0)
      {
        return true;
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
  return c == ' ';
}
