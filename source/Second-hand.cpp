#include "Second-hand.hpp"
#include "Coordinates.hpp"
#include "math.hpp"
#include "output.hpp"
#include <ctime>
#include <vector>

Second_hand::Second_hand()
{
  current_second = 1;
}

void Second_hand::update(const int &new_size_x, const int &new_size_y)
{
  Coordinate_center(center, new_size_x, new_size_y);
  Radius(radius, 3, new_size_x, new_size_y);
  Coordinates_circle(radius, circle_second);
  Coordinate_upgrade(circle_second);
}

bool Second_hand::Second_update(bool flag)
{
  time_t now = time(nullptr);
  tm *time = localtime(&now);
  if (flag)
  {
    return (current_second != time->tm_sec) ? (current_second = time->tm_sec, true) : false;
  }
  return current_second != time->tm_sec;
}

void Second_hand::build1()
{
  line.clear();
  switch (current_second)
  {
  case 0:
    for (int i = 1; i <= radius; i++)
    {
      line.push_back(Coordinates{0, i});
    }
    return;
  case 15:
    for (int i = 1; i <= radius * 2; i++)
    {
      line.push_back(Coordinates{i, 0});
    }
    return;
  case 30:
    for (int i = 1; i <= radius; i++)
    {
      line.push_back(Coordinates{0, i});
    }
    return;
  case 45:
    for (int i = 1; i <= radius * 2; i++)
    {
      line.push_back(Coordinates{i, 0});
    }
    return;
  }
}

void Second_hand::draw()
{
  if (Second_update(true))
  {
    int temp = current_second % 15;
    if (temp == 0)
    {
      build1();
    }
    else
    {
      temp = ((current_second > 15 && current_second < 30) || (current_second > 45 && current_second < 60)) ? 15 - temp : temp;
      Degree(temp * 6, second_stop, circle_second);
      second_stop.x += (current_second > 30) ? 1 : 0;
      Coordinates_line(second_stop, line);
    }

    shift.x = (current_second < 31) ? 1 : -1;
    shift.y = (current_second > 15 && current_second < 46) ? 1 : -1;

    for (size_t i = 0; i < line.size(); i++)
    {
      output_char(center.x + line[i].x * shift.x, center.y + line[i].y * shift.y, ' ', 40);
    }
    /*
    test_function(circle_second);
    test_function(line);
    */
  }
}

void Second_hand::clear()
{
  if (Second_update(false))
  {
    for (size_t i = 0; i < line.size(); i++)
    {
      output_char(center.x + line[i].x * shift.x, center.y + line[i].y * shift.y, ' ', 47);
    }
  }
  /*

  test_function(line);
  */
}
