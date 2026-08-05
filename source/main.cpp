// #include "Hour-hand.hpp"
// #include "Minute-hand.hpp"
#include "Second-hand.hpp"
#include "Simple_string.hpp"
#include "output.hpp"
//  #include "date.hpp"
#include "Coordinates.hpp"
#include "Settings_clock.hpp"
#include "background.hpp"
#include "input.hpp"
#include "watch_face.hpp"
#include <unistd.h>

bool correct_term_size(const Coordinates &size,const short width)
{
  return (size.x > (15 * width) && size.y > 15 && size.x < (1024 * width) && size.y < 1024);
}

int main()
{
  Coordinates term_size;
  Coordinates past_term_size;
  bool color = false;
  bool past_color = false;

  Settings_clock setting;
  setting.new_settings();

  Second_hand second(setting.get_width(),setting.get_second_color(color),setting.get_background_color(color));
  bool temp;

  setting_term_mode(true);
  hide_cursor(true);

  get_term_size(term_size);
  Simple_string canvas(term_size.x * term_size.y);

  while (!check_buffer(temp, color))
  {

    get_term_size(term_size);
    
    if (correct_term_size(term_size,setting.get_width()))
    {
      if (term_size != past_term_size || color != past_color)
      {
        hide_cursor(true);
        canvas.update_size_spaces(term_size.x * term_size.y);
        draw_background(canvas.get_spaces(), setting.get_background_color(color));
        draw_watch_face(term_size,setting.get_width(),setting.get_circle_color(color),setting.get_number_color(color),setting.get_circle_symbol(),setting.get_num_clock_symbols());
        second.update(term_size,setting.get_second_color(color),setting.get_background_color(color));
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
