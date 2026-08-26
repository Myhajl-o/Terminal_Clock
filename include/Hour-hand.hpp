#ifndef HOUR_HAND_HPP
#define HOUR_HAND_HPP

#include "Coordinates.hpp"
#include "Color_object.hpp"
#include <vector>

class Hour_hand
{
  short radius;
  Coordinates center;
  std::vector<Coordinates> circle_hour;
  Coordinates hour_tick[2];
  Coordinates hour_stop;
  std::vector<Coordinates> line;
 
  short mini_radius;
  short mini_shift;
  Coordinates mini_center;
  std::vector<Coordinates> temp_circle;
  std::vector<Coordinates> mini_circle;
  Coordinates mini_tick[2];

  Coordinates shift;
  const char* const*symbols;
  bool clearing;
  bool drawing;

  short width;
  bool show_mini_circle;
  Color_object draw_color;
  Color_object mini_circle_color;
  Color_object clear_color;

  short current_second;
  short current_hour;

  void calculation_coordinate_line();
  void calculation_mini_circle(const short temp);
  short current_symbol(const unsigned short &i);
  bool second_update();
  bool hour_update(const bool flag);

public:
  Hour_hand(const short wi,const Color_object*draw_c,const Color_object clear_c,const char* const*sym,const bool show_min_circ);

  void update(const Coordinates &new_size,const Color_object*draw_c,const Color_object clear_c);

  void clear();

  void draw();

};

#endif
