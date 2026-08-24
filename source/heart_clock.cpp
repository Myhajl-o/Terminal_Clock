#include "Hour-hand.hpp"
#include "Minute-hand.hpp"
#include "Second-hand.hpp"
#include "bg_string.hpp"
//  #include "date.hpp"
#include "Coordinates.hpp"
#include "Settings_clock.hpp"
#include "background.hpp"
#include "watch_face.hpp"
#include "addition_functional.hpp"

#include "input.hpp"
#include "output.h"
#include "parsing.h"
#include "timedate.hpp"

#include <unistd.h>

bool correct_term_size(const Coordinates &size,const short width)
{
  static const short min = 15,max = 1024;
  return (size.x > (min * width) && size.y > min && size.x < (max * width) && size.y < max);
}

int main(const int argc,const char*const*argv)
{
  char clear_sym[6] = {32,0,0,0,0,1};
  update_time();
  short flag = 0;
  if(argc > 1)
  {
    if((!parsing_main(&flag,argv)) || !flag)
    {
      return 1;
    }
  }

  if(flag > 1)
  {
    addition_functional(flag);
    return 0;
  }

  Coordinates term_size;
  Coordinates past_term_size;
  bool color = false;
  bool past_color = false;

  Settings_clock set;

  Second_hand second(set.get_width(),set.get_sec_color(color),set.get_bg_color(color),set.get_sec_symbols());
  Minute_hand minute(set.get_width(),set.get_min_color(color),set.get_bg_color(color),set.get_min_symbols());
  Hour_hand hour(set.get_width(),set.get_min_color(color),set.get_bg_color(color),set.get_min_symbols());
  bool temp;

  setting_term_mode(true);
  hide_cursor(true);

  get_term_size(term_size);
  bg_string canvas(term_size.x,set.get_bg_symbol());
  bg_string cleaner(term_size.x,clear_sym);

  while (!check_buffer(temp, color))
  {
    get_term_size(term_size);
    if(flag)
    {
      term_size.x = term_size.x - (term_size.x >> 2);
      term_size.y = term_size.y - (term_size.y >> 2);
    }
    if (correct_term_size(term_size,set.get_width()))
    {
      if (term_size != past_term_size || color != past_color)
      {
        hide_cursor(true);
        canvas.update_size_spaces(term_size.x);
        cleaner.update_size_spaces(term_size.x);
        draw_background(term_size.y,canvas.get_spaces(), set.get_bg_color(color));
        draw_watch_face(term_size,set.get_width(),set.get_wf_color(color),set.get_circ_symbol(),set.get_num_symbols(),set.get_num_shift());
        second.update(term_size,set.get_sec_color(color),set.get_bg_color(color));
        minute.update(term_size,set.get_min_color(color),set.get_bg_color(color));
        hour.update(term_size,set.get_min_color(color),set.get_bg_color(color));
      }

      update_time();

      second.clear();
      minute.clear();
      hour.clear();

      second.draw();
      minute.draw();
      hour.draw();
    }
    else
    {
      full_clear_term(term_size.y,cleaner.get_spaces());
    }
    if(flag)
    {
      setting_term_mode(false);
      hide_cursor(false);
      clear_term();
      set_cursor(0,term_size.y + 1);
      return 0;
    }
    past_term_size = term_size;
    past_color = color;

    usleep(100000);
  }

  setting_term_mode(false);
  hide_cursor(false);
  full_clear_term(term_size.y,cleaner.get_spaces());

  return 0;
}
