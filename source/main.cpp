// #include "Hour-hand.hpp"
// #include "Minute-hand.hpp"
#include "Second-hand.hpp"
#include "output.hpp"
//  #include "date.hpp"
#include "Coordinates.hpp"
#include "background.hpp"
#include "input.hpp"
#include "watch_face.hpp"
#include <unistd.h>

bool incorrect_term_size(const Coordinates &size)
{
  return (size.x < 30 || size.y < 15 || size.x > 2048 || size.y > 1024);
}

int main()
{
  Coordinates term_size;
  Coordinates past_term_size;

  Second_hand second;
  bool temp;

  bool color = false;
  bool past_color = false;

  block(false);
  cursor(true);

  while (!check_buffer(temp, color))
  {

    get_term_size(term_size);

    if (!incorrect_term_size(term_size))
    {
      if (term_size != past_term_size || color != past_color)
      {
        clear();
        cursor(true);
        change_color(color);
        background(term_size);
        watch_face(term_size);
        second.update(term_size);
      }
      second.clear();
      second.draw();
    }
    else
    {
      clear();
    }

    past_term_size = term_size;
    past_color = color;

    usleep(100000);
  }

  block(true);
  cursor(false);
  clear();

  return 0;
}
