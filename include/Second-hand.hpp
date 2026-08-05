#ifndef SECOND_HAND_HPP
#define SECOND_HAND_HPP

#include "Coordinates.hpp"
#include "Color_object.hpp"
#include <vector>

class Second_hand
{
  short radius;
  Coordinates center;
  std::vector<Coordinates> circle_second;
  Coordinates second_stop;
  std::vector<Coordinates> line;
  Coordinates shift;
  char**symbols;
  bool clearing;
  bool drawing;

  short width;
  Color_object draw_color;
  Color_object clear_color;

  short current_second;

  void calculation_coordinate_line();
  short current_symbol(const unsigned short &i);
  bool second_update(bool flag);

public:
  Second_hand(const short wi,const Color_object draw_c,const Color_object clear_c,char**sym);

  void update(const Coordinates &new_size,const Color_object draw_c,const Color_object clear_c);

  void clear();

  void draw();
};

#endif
