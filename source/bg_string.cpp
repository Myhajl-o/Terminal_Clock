#include "bg_string.hpp"
#include <cstring>

bg_string::bg_string(const short size):all_size(size)
{
  spaces = new char[all_size + 1];
  std::memset(spaces,' ',all_size);
  spaces[all_size] = '\0';
}

void bg_string::upgrade_size(const short new_size)
{
  char*temp = new char[new_size + 1];
  std::memset(temp,' ', new_size);
  delete[] spaces;
  spaces = temp;
}

void bg_string::update_size_spaces(const short size)
{
  if(all_size < size)
  {
    upgrade_size(size);
    spaces[size] = '\0';
    all_size = size;
  }
  else
  {
    spaces[past_size] = ' ';
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
  delete[] spaces;
}

