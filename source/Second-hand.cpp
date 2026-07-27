#include "Second-hand.hpp"
#include "Coordinates.hpp"
#include "math.hpp"
#include "output.hpp"
#include <ctime>
#include <vector>

Second_hand::Second_hand() {
  current_second = 60;
  clearing = false;
}

void Second_hand::update(const Coordinates &new_size) {
  clearing = false;
  Coordinate_center(center, new_size);
  Radius(radius, 3, center);
  Coordinates_circle(radius, circle_second);
  Coordinate_upgrade(circle_second);
}

bool Second_hand::Second_update(bool flag) {
  time_t now = time(NULL);
  tm *time = localtime(&now);
  if (flag) {
    return (current_second != time->tm_sec)
               ? (current_second = time->tm_sec, true)
               : false;
  }
  return current_second != time->tm_sec;
}

void Second_hand::current_symbol(char &symbol, std::size_t &i) {
  char diagonal =
      (current_second < 16 || (current_second > 30 && current_second < 45))
          ? '/'
          : '\\';
  if (i == 0) {
    symbol = (line[i].x == line[i + 1].x)   ? '|'
             : (line[i].y == line[i + 1].y) ? '-'
                                            : diagonal;
  } else if (i == line.size() - 1) {
    symbol = (line[i].x == line[i - 1].x)   ? '|'
             : (line[i].y == line[i - 1].y) ? '-'
                                            : diagonal;
  } else {
    if (line[i - 1].x == line[i].x && line[i].x == line[i + 1].x) {
      symbol = '|';
    } else if (line[i - 1].y == line[i].y && line[i].y == line[i + 1].y) {
      symbol = '-';
    } else {
      symbol = diagonal;
    }
  }
}

void Second_hand::draw() {
  if (Second_update(true)) {
    int temp = current_second % 15;
    if (temp == 0) {
      line.clear();
      Coordinates value;
      int dilatation;
      if (current_second == 15 || current_second == 45) {
        value.reset(1, 0);
        dilatation = 2;
      } else {
        value.reset(0, 1);
        dilatation = 1;
      }
      for (int i = 1; i <= radius * dilatation; i++) {
        line.push_back(Coordinates(i * value.x, i * value.y));
      }
    } else {
      temp = ((current_second > 15 && current_second < 30) ||
              (current_second > 45 && current_second < 60))
                 ? 15 - temp
                 : temp;
      Degree(temp * 6, second_stop, circle_second);
      second_stop.x += (current_second > 30) ? 1 : 0;
      Coordinates_line(second_stop, line);
    }
    shift.x = (current_second < 31) ? 1 : -1;
    shift.y = (current_second > 15 && current_second < 46) ? 1 : -1;

    for (std::size_t i = 0; i < line.size(); i++) {
      current_symbol(symbol, i);
      output_symbols(center.x + line[i].x * shift.x,
                     center.y + line[i].y * shift.y, &symbol, 47);
    }
    clearing = true;
  }
}

void Second_hand::clear() {
  if (Second_update(false) && clearing) {
    symbol = ' ';
    for (short i = 0; i < (short)line.size(); i++) {
      output_symbols(center.x + line[i].x * shift.x,
                     center.y + line[i].y * shift.y, &symbol, 47);
    }
  }
}
