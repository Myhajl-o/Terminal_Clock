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

bool correct_term_size(const Coordinates &size)
{
  return (size.x > 30 && size.y > 15 && size.x < 2048 && size.y < 1024);
}

int main()
{
  Coordinates term_size;
  Coordinates past_term_size;

  Second_hand second;
  bool temp;

  bool color = false;
  bool past_color = false;

  setting_term_mode(true);
  hide_cursor(true);

  while (!check_buffer(temp, color))
  {

    get_term_size(term_size);

    if (correct_term_size(term_size))
    {
      if (term_size != past_term_size || color != past_color)
      {
        hide_cursor(true);
        change_color(color);
        draw_background(term_size);
        draw_watch_face(term_size);
        second.update(term_size);
      }
      second.clear();
      second.draw();
    }
    else
    {
      clear_term();
    }

    past_term_size = term_size;
    past_color = color;

    usleep(100000);
  }

  setting_term_mode(false);
  hide_cursor(false);
  clear_term();

  return 0;
}
