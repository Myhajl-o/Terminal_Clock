#pragma once
#include "Coordinates.hpp"
#include <vector>

class Second_hand {
  short radius;
  Coordinates center;
  std::vector<Coordinates> circle_second;
  Coordinates second_stop;
  std::vector<Coordinates> line;
  Coordinates shift;
  char symbol[2];
  bool clearing;

  short current_second;

  void current_symbol(const short &i);
  bool Second_update(bool flag);

public:
  Second_hand();

  void update(const Coordinates &new_size);

  void clear();

  void draw();
};
