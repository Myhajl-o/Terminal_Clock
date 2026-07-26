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
  char symbol;
  bool clearing;

  int current_second;

  void current_symbol(char &symbol, std::size_t &i);
  bool Second_update(bool flag);

public:
  Second_hand();

  void update(const Coordinates &new_size);

  void clear();

  void draw();
};
