#include "Simple_string.hpp"
#include <cstring>

Simple_string::Simple_string(unsigned int _size)
{
  spaces = new char[_size + 1];
  std::memset(spaces,' ',_size);
  spaces[_size] = '\0';
  all_size = _size;
  current_size = _size;
}

void Simple_string::upgrade_size(const unsigned int&new_size)
{
  char*temp = new char[new_size + 1];
  std::memset(temp, ' ', new_size);
  delete[] spaces;
  spaces = temp;
}

void Simple_string::update_size_spaces(unsigned int _size)
{
  if(all_size < _size)
  {
    upgrade_size(_size);
    spaces[_size] = '\0';
    all_size = _size;
    current_size = _size;
  }
  else
  {
    spaces[current_size] = ' ';
    spaces[_size] = '\0';
    current_size = _size;
  }
}

char* Simple_string::get_spaces()
{
  return spaces;
}

Simple_string::~Simple_string()
{
  delete[] spaces;
}

