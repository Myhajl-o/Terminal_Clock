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
    c.main_back = 0;
    c.main_front = 0;
  }

  Color_object(const short b,const short f,const short mb,const short mf)
  {
    c.back = b;
    c.front = f;
    c.main_back = mb;
    c.main_front = mf;
  }

  void reset(const short b,const short f,const short mb,const short mf)
  {
    c.back = b;
    c.front = f;
    c.main_back = mb;
    c.main_front = mf;
  }
};

#endif
