#ifndef COLOR_OBJECT_HPP
#define COLOR_OBJECT_HPP

#include "Colors.h"

struct Color_object
{
  Colors c;

  Color_object()
  {
    c.back = 0;
    c.front = 0;
  }

  Color_object(const short b,const short f)
  {
    c.back = b;
    c.front = f;
  }

  void reset(const short b,const short f)
  {
    c.back = b;
    c.front = f;
  }
};

#endif
