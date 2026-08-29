/* A very simple timedate library, created with a single goal in mind:
 * to make it easier to access the current time in a project.
 * And this library successfully accomplishes its task.
 *
 * This library is used in the files heart_clock.cpp,
 * Second-hand.cpp, Minute-hand.cpp, Hour-hand.cpp, and Date_window.cpp.*/




#include "timedate.hpp"
#include <ctime>


short&cur_second()
{
  static short second;
  return second;
}

short&cur_minute()
{
  static short minute;
  return minute;
}

short&cur_hour()
{
  static short hour;
  return hour;
}

short&cur_day()
{
  static short day;
  return day;
}

short&cur_wday()
{
  static short wday;
  return wday;
}

short&cur_month()
{
  static short month;
  return month;
}

short&cur_year()
{
  static short year;
  return year;
}

void update_time()
{
  time_t now = time(NULL);
  tm*time = localtime(&now);
  cur_second() = time->tm_sec;
  cur_minute() = time->tm_min;
  cur_hour() = time->tm_hour;
  cur_day() = time->tm_mday;
  cur_wday() = time->tm_wday;
  cur_month() = time->tm_mon + 1;
  cur_year() = time->tm_year + 1900;
}






