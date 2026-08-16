#ifndef SIMPLE_STRING_HPP
#define SIMPLE_STRING_HPP

#include "Coordinates.hpp"

class Simple_string
{
  char *spaces;
  unsigned int all_size;
  unsigned int current_size;


  void upgrade_size(const unsigned int&new_size);

  public:
  Simple_string(unsigned int _size);

  void update_size_spaces(const Coordinates size,bool flag);

  void fixed_size(const Coordinates size);

  char* get_spaces();

  ~Simple_string();
};

#endif
