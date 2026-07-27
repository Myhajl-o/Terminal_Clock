#pragma once

struct Coordinates
{
  short x;
  short y;

  Coordinates()
  {
    x = 0;
    y = 0;
  }
  Coordinates(short _x, short _y)
  {
    x = _x;
    y = _y;
  }
  Coordinates(const Coordinates &other)
  {
    x = other.x;
    y = other.y;
  }
  void reset(short _x, short _y)
  {
    x = _x;
    y = _y;
  }
  bool operator!=(const Coordinates &other) const
  {
    return (x != other.x || y != other.y);
  }
};
