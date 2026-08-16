#include "Simple_string.hpp"
#include "Coordinates.hpp"
#include <cstring>

Simple_string::Simple_string(unsigned int _size)
{
  spaces = new char[_size + 1];
  std::memset(spaces,' ',_size);
//  for(short i = 1; i < size.y;i++) spaces[i * size.x] = '\n';
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

void Simple_string::update_size_spaces(const Coordinates size,bool flag)
{
  if(flag)
  {
    fixed_size(size);
    return;
  }
  unsigned int _size = size.x * size.y;
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

void Simple_string::fixed_size(const Coordinates size)
{
  for(short i = 1; i < size.y;i++) spaces[i * size.x] = '\n';
  spaces[(size.x * size.y) - 1] = '\n';
  spaces[size.x * size.y] = '\0';
}

char* Simple_string::get_spaces()
{
  return spaces;
}

Simple_string::~Simple_string()
{
  delete[] spaces;
}

