#include "Simple_string.hpp"
#include <cstring>

Simple_string::Simple_string(unsigned int _size)
{
  symbols = new char[_size + 1];
  std::memset(symbols,' ',_size);
  symbols[_size] = '\0';
  all_size = _size;
  current_size = _size;
}

void Simple_string::upgrade_size(unsigned int new_size)
{
  char*temp = new char[new_size + 1];
  std::memset(temp, ' ', new_size);
  delete[] symbols;
  symbols = temp;
}

void Simple_string::update_array(unsigned int _size)
{
  if(all_size < _size)
  {
    upgrade_size(_size);
    symbols[_size] = '\0';
    all_size = _size;
    current_size = _size;
  }
  else
  {
    symbols[current_size] = ' ';
    symbols[_size] = '\0';
    current_size = _size;
  }
}

char* Simple_string::get_array()
{
  return symbols;
}

Simple_string::~Simple_string()
{
  delete[] symbols;
}

