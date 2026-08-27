#ifndef MINUTE_HAND_HPP
#define MINUTE_HAND_HPP

#include "Coordinates.hpp"
#include "Color_object.hpp"
#include <vector>

class Minute_hand
{
  short radius;
  Coordinates center;
  std::vector<Coordinates> circle_minute;
  Coordinates minute_tick[14];
  Coordinates minute_stop;
  std::vector<Coordinates> line;
  Coordinates shift;
  const char* const*symbols;
  bool clearing;
  bool drawing;

  short width;
  Color_object draw_color;
  Color_object clear_color;

  short current_second;
  short current_minute;

  void calculation_coordinate_line();
  short current_symbol(const unsigned short &i);
  bool second_update();
  bool minute_update(const bool flag);

public:
  Minute_hand(const short wi,const Color_object draw_c,const Color_object clear_c,const char* const*sym);

  void update(const Coordinates &new_size,const Color_object draw_c,const Color_object clear_c);

  void clear();

  void draw();

};

#endif
