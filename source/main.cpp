// #include "Hour-hand.hpp"
// #include "Minute-hand.hpp"
// #include "Second-hand.hpp"
#include "output.hpp"
//  #include "date.hpp"
#include "Coordinates.hpp"
#include "input.hpp"
#include <unistd.h>

bool incorrect_term_size(const int &x, const int &y) {
  return (x < 13 || y < 7 || x > 9999998 || y > 4999999);
}

int main() {

  Coordinates term_size;
  Coordinates past_term_size;

  get_term_size(term_size.x, term_size.y);
  /*
    Second_hand *second = new Second_hand();
    Minute_hand *minute = new Minute_hand();
    Hour_hand *hour = new Hour_hand();
  */
  bool temp;

  block(false);

  past_term_size.x = 0;
  past_term_size.y = 0;

  while (!check_buffer(temp)) {

    get_term_size(term_size.x, term_size.y);

    if (!incorrect_term_size(term_size.x, term_size.y)) {
      if (term_size.x != past_term_size.x || term_size.y != past_term_size.y) {
        clear();
        background(term_size.x, term_size.y);
        watch_face(term_size.x, term_size.y);
      }

    } else {
      clear();
    }

    past_term_size.x = term_size.x;
    past_term_size.y = term_size.y;

    usleep(100000);
  }

  block(true);
  clear();
  /*
    delete second;
    delete minute;
    delete hour;
  */
  return 0;
}
