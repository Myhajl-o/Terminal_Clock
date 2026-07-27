#pragma once

struct Coordinates {
  int x;
  int y;

  Coordinates() {
    x = 0;
    y = 0;
  }
  Coordinates(int _x, int _y) {
    x = _x;
    y = _y;
  }
  Coordinates(const Coordinates &other) {
    x = other.x;
    y = other.y;
  }
  void reset(int _x, int _y) {
    x = _x;
    y = _y;
  }
  bool operator!=(const Coordinates &other) const {
    return (x != other.x || y != other.y);
  }
};
