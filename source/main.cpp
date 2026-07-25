// #include "Hour-hand.hpp"
// #include "Minute-hand.hpp"
#include "Second-hand.hpp"
#include "output.hpp"
//  #include "date.hpp"
#include "Coordinates.hpp"
#include "input.hpp"
#include <unistd.h>

bool incorrect_term_size(const Coordinates &size)
{
  return (size.x < 20 || size.y < 10 || size.x > 9999998 || size.y > 4999999);
}

int main()
{

  Coordinates term_size;
  Coordinates past_term_size = Coordinates{0, 0};

  get_term_size(term_size);

  Second_hand *second = new Second_hand();
  /*   Minute_hand *minute = new Minute_hand();
     Hour_hand *hour = new Hour_hand();
   */
  bool temp;

  block(false);

  while (!check_buffer(temp))
  {

    get_term_size(term_size);

    if (!incorrect_term_size(term_size))
    {
      if (term_size != past_term_size)
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
