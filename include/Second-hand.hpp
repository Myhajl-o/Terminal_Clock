#ifndef SECOND_HAND_HPP
#define SECOND_HAND_HPP

#include "Coordinates.hpp"
#include <vector>

class Second_hand
{
  short radius;
  Coordinates center;
  std::vector<Coordinates> circle_second;
  Coordinates second_stop;
  std::vector<Coordinates> line;
  Coordinates shift;
  char symbol[2];
  bool clearing;

  short current_second;

  void calculation_coordinate_line();
  void current_symbol(const unsigned short &i);
  bool second_update(bool flag);

public:
  Second_hand();

  void update(const Coordinates &new_size);

  void clear();

  void draw();
};

#endif
