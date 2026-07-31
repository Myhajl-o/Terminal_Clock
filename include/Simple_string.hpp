#ifndef SIMPLE_STRING_HPP
#define SIMPLE_STRING_HPP

#include <cstring>

struct Simple_string
{
  char *symbols;
  unsigned int size;
  Simple_string(unsigned int _size)
  {
    symbols = new char[_size + 1];
    std::memset(symbols, ' ', _size);
    symbols[_size] = '\0';
    size = _size;
  }

  ~Simple_string()
  {
    delete[] symbols;
  }
};

#endif
