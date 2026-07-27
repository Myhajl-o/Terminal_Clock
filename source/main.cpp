// #include "Hour-hand.hpp"
// #include "Minute-hand.hpp"
#include "Second-hand.hpp"
#include "output.hpp"
//  #include "date.hpp"
#include "Coordinates.hpp"
#include "input.hpp"
#include <unistd.h>

bool color = false;

bool incorrect_term_size(const Coordinates &size)
{
  return (size.x < 20 || size.y < 10 || size.x > 32766 || size.y > 16383);
}

int main()
{

  Coordinates term_size;
  Coordinates past_term_size;

  Second_hand *second = new Second_hand();
  /*   Minute_hand *minute = new Minute_hand();
     Hour_hand *hour = new Hour_hand();
   */
  bool temp;
  bool past_color = false;

  block(false);

  while (!check_buffer(temp, color))
  {

    get_term_size(term_size);

    if (!incorrect_term_size(term_size))
    {
      if (term_size != past_term_size || color != past_color)
      {
        clear();
        background(term_size);
        watch_face(term_size);
        second->update(term_size);
      }
      second->clear();
      second->draw();
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
  clear();

  delete second;
  /*   delete minute;
     delete hour;
   */
  return 0;
}
