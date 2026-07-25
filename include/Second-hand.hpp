#pragma once
#include "Coordinates.hpp"
// #include <string>
#include <vector>

class Second_hand
{
  int radius;
  Coordinates center;
  std::vector<Coordinates> circle_second;
  Coordinates second_stop;
  std::vector<Coordinates> line;
  Coordinates shift;

  int current_second;

  bool Second_update(bool flag);

public:
  Second_hand();

  void update(const int &new_size_x, const int &new_size_y);

  void clear();

  void draw();
};
