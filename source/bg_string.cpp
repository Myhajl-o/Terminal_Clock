#include "bg_string.hpp"
#include <stdlib.h>

void bg_string::fill_array_1b(short index)
{
  for(; index < all_size; index++)
  {
    spaces[index] = symbol[0];
  }
}

void bg_string::fill_array_234b(short index)
{
  for(; index < all_size; index++)
  {
    spaces[index] = symbol[index%size_sym];
  }
}

bg_string::bg_string(const short size,const char*sym):symbol(sym)
{
  size_sym = symbol[5];
  all_size = size * size_sym;
  past_size = all_size;
  spaces = (char*)malloc(all_size + 1);
  if(size_sym == 1) fill_array_1b(0);
  else fill_array_234b(0);
  spaces[all_size] = '\0';
}

void bg_string::upgrade_size()
{
  spaces = (char*)realloc(spaces,all_size + 1);
  if(size_sym == 1) fill_array_1b(past_size);
  else fill_array_234b(past_size);
}

void bg_string::update_size_spaces(short size)
{
  size *= size_sym;
  if(all_size < size)
  {
    all_size = size;
    upgrade_size();
    spaces[all_size] = '\0';
  }
  else
  {
    if(size_sym == 1)spaces[past_size] = symbol[0];
    else fill_array_234b(0);
    spaces[size] = '\0';
  }
  past_size = size;
}

char* bg_string::get_spaces()
{
  return spaces;
}

bg_string::~bg_string()
{
  free(spaces);
}

