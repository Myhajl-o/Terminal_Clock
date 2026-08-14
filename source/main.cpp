// #include "Hour-hand.hpp"
// #include "Minute-hand.hpp"
#include "Second-hand.hpp"
#include "Simple_string.hpp"
#include "output.h"
//  #include "date.hpp"
#include "Coordinates.hpp"
#include "Settings_clock.hpp"
#include "background.hpp"
#include "parsing.h"
#include "input.hpp"
#include "watch_face.hpp"
#include <unistd.h>

bool correct_term_size(const Coordinates &size,const short width)
{
  return (size.x > (15 * width) && size.y > 15 && size.x < (1024 * width) && size.y < 1024);
}

int main(const int argc,const char*const*argv)
{
  parsing_main(argc,argv);
  Coordinates term_size;
  Coordinates past_term_size;
  bool color = false;
  bool past_color = false;

  Settings_clock set;
  bool correct_read = parsing_conf(set.get_array_numbers(),set.get_array_symbols(),set.get_size_num(),set.get_size_sym());
  set.new_settings(correct_read);

  Second_hand second(set.get_width(),set.get_sec_color(color),set.get_bg_color(color),set.get_sec_symbols());
  bool temp;

  setting_term_mode(true);
  hide_cursor(true);

  get_term_size(term_size);
  Simple_string canvas(term_size.x * term_size.y);

  while (!check_buffer(temp, color))
  {

    get_term_size(term_size);
    
    if (correct_term_size(term_size,set.get_width()))
    {
      if (term_size != past_term_size || color != past_color)
      {
        hide_cursor(true);
        canvas.update_size_spaces(term_size.x * term_size.y);
        draw_background(canvas.get_spaces(), set.get_bg_color(color));
        draw_watch_face(term_size,set.get_width(),set.get_wf_color(color),set.get_circ_symbol(),set.get_num_symbols(),set.get_num_shift());
        second.update(term_size,set.get_sec_color(color),set.get_bg_color(color));
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
