/*
 * The math.cpp file is the math library for this project. It implements, from scratch and without using
 * any third-party code, all the necessary mathematical functions required by this project. Specifically,
 * it includes a function for calculating the arctangent, a function for calculating an array of coordinates
 * for drawing a circle, a function to find the coordinate closest to a specific degree, and a function
 * to calculate an array of coordinates for a line segment. This library demonstrates how to implement
 * these functions in code.
 *
 * Virtually all the functions here are well-optimized, which is a huge advantage, since this utility
 * needs to run very quickly.
 *
 * ! This library is tailored specifically for this project; in order to
 * use it elsewhere, it must be adapted to specific needs as required.*/





#include "math.hpp"
#include "Coordinates.hpp"
#include <vector>

#define convert 180.0f / 3.1415f

inline float absolute_number(float number)
{
  return (number < 0) ? -number : number;
}


// The simple_pow function calculates a fractional number
// raised to an integer power.
//
// ! This function is not intended for calculating fractional
// or negative powers.
//
// This function is used in the arctan function.
double simple_pow(double num,short power)
{
    double result = num;
    while(power > 1){result *= num;power--;}
    return result;
}


// The arctan function is a manual implementation in code
// of the standard trigonometric function arctangent.
// It uses
// Taylor series to compute the arctangent.

// The function is used in the Coordinate_degree and
// Coordinate_circle_degrees functions.
float arctan(short a,short b)
{
    static const double degree45 = 0.785398;
    double x,arctan,temp;
    
    bool flag = false;
    bool sub = true;
    
    if(a>b){ x = (double)b / (double)a;flag = true;}
    else if(a==b){return (float)degree45;}
    else{ x = (double)a / (double)b;}
    
    arctan = x;
    temp = 1;
    for(short i = 3; temp > 0.0001 && i < 100;i+=2,sub = !sub)
    {
        temp = simple_pow(x,i) / i;
        if(sub)arctan -= temp;
        else arctan += temp;
    }
    if(flag)
    {
        arctan = degree45 + (degree45 - arctan);
    }
    return (float)arctan;
}


// The Coordinate_center function is designed to calculate
// the center of the terminal window. The function calculates
// the center by dividing the terminal width by 2 and
// dividing the terminal height by 2.
//
// This function is used in the watch_face.cpp,
// Second-hand.cpp, Minute-hand.cpp, Hour-hand.cpp
// and Date_window.cpp files.
void Coordinate_center(Coordinates &center, const Coordinates &size)
{
  center.reset(size.x / 2, size.y / 2);
}

// The Calculation_radius function calculates a radius that will
// fit the size of the terminal. For example, if the terminal width
// is less than the height, the radius will be calculated relative
// to the width rather than the height. This is done so that
// the circle drawn using this radius fits exactly into the
// terminal window.
//
// This function is used in the watch_face.cpp,
// Second-hand.cpp, Minute-hand.cpp, Hour-hand
// and Date_window.cpp files.
void Calculation_radius(short &radius, short backdown, const Coordinates &center,const short width)
{
  if (center.x < (center.y * width))
  {
    radius = (center.x / width) - backdown;
  }
  else
  {
    radius = center.y - backdown;
  }
}

// The Coordinates_circle function calculates the coordinates for
// drawing a 1/4 circle relative to the initial coordinates
// x:0, y:0. That is, the function calculates raw data for
// drawing a 1/4 circle; to use them, certain mathematical
// calculations must be performed.
// The function first calculates a 1/8 circle using
// Bresenham's algorithm for drawing arcs or circles.
// The coordinates for the 1/4 circle are found by
// reflecting the previous coordinates that were
// obtained using Bresenham's algorithm.
//
// This function is used in the watch_face.cpp,
// Second-hand.cpp, Minute-hand.cpp and Hour-hand.cpp files.
void Coordinates_circle(std::vector<Coordinates> &circle,const short radius)
{
  circle.clear();
  short d = 3 - 2 * radius;
  Coordinates temp(0, radius);
  circle.push_back(temp);

  do
  {
    if (d < 0)
    {
      d = d + 4 * temp.x + 6;
      temp.x++;
    }
    else
    {
      d = d + 4 * (temp.x - temp.y) + 10;
      temp.x++;
      temp.y--;
    }
    circle.push_back(temp);
  } while (temp.x == temp.y || temp.x < temp.y);

  circle.resize(temp.x * 2);
  for (short i = temp.x * 2 - 1; i >= temp.x; i--)
  {
    circle[i].x = circle[(temp.x * 2 - 1) - i].y;
    circle[i].y = circle[(temp.x * 2 - 1) - i].x;
  }
}

// The Coordinate_upgrade function expands the coordinate array.
// It expands the array and increases the x coordinate.
// This is done to make the circle wider.
//
//! The function is designed for an array of 1/4 circle coordinates;
// if anything else is passed to it, the result may be incorrect.
//
// This function is used in the watch_face.cpp
// Second-hand.cpp, Minute-hand.cpp and Hour-hand.cpp files.
void Coordinate_upgrade(std::vector<Coordinates> &circle,const short width)
{
  if(width == 1)
  {
    return;
  }
  static std::vector<Coordinates> temp;
  temp.clear();
  temp = circle;
  circle.resize(circle.size() * width - 1);
  short j = 0;
  short add;

  for (unsigned short i = 0; i < circle.size(); i += width)
  {
    add = temp[j].x < temp[j + 1].x;

    for(short add_i = 0; add_i < width; add_i++)
    {
      circle[i+add_i].x = temp[j].x * width + (add * add_i);
      circle[i+add_i].y = temp[j].y;
    }

    j++;
  }
}

// The Coordinate_degree function calculates the closest coordinate
// of the circle by its degree to the degree passed into the function.
// The degree of the coordinate is calculated relative to the zero
// coordinate (x:0, y:0), using the formula arctan(x / y).
// This function is used for building a watch face
// and for similar tasks.
//
// ! The function is designed for an array of 1/4 circle coordinates;
// if anything else is passed to it, the result may be incorrect.
//
// This function is used in the Hour-hand.cpp file.
void Coordinate_degree(Coordinates &tick_element,const short degree,const std::vector<Coordinates> &circle,const short width)
{
  float difference[2];
  unsigned short i;
  if(degree < 42)
  {
    i = 2;
  }
  else if(degree < 66)
  {
    i = circle.size() >> 2;
  }
  else
  {
    i = circle.size() >> 1;
  }

  difference[0] = absolute_number(degree - (convert * arctan(circle[1].x,circle[1].y * width)));

  while(i < circle.size())
  {
    difference[1] = absolute_number(degree - (convert * arctan(circle[i].x,circle[i].y * width)));
    if (difference[0] < difference[1])
    {
      tick_element = circle[i - 1];
      return;
    }
    difference[0] = difference[1];
    i++;
  }
}


// The Coordinate_circle_degrees function calculates the nearest coordinates
// of a 1/4 circle that are closest in degrees to where the numbers
// are positioned on the watch face. In other words, it takes a pre-computed 
// array of coordinates and iterates through it to find the coordinates, 
// which are then used to draw the hands or numbers.
//
// The function is used in the files watch_face.cpp, Second-hand.cpp, and Minute-hand.cpp.
void Coordinate_circle_degrees(Coordinates *ticks,const std::vector<Coordinates>&circle,const short width)
{
  float difference[2];
  static const short degrees[14] = {6,12,18,24,30,36,42,48,54,60,66,72,78,84};
  short i_deg = 0;
  difference[0] = absolute_number(degrees[0] - (convert * arctan(circle[1].x,circle[1].y * width)));

  for(unsigned short i = 2; i < circle.size() && i_deg < 14; i++)
  {
    difference[1] = absolute_number(degrees[i_deg] - (convert * arctan(circle[i].x,circle[i].y * width)));
    if(difference[0] < difference[1])
    {
      ticks[i_deg] = circle[i - 1];
      i_deg++;
      difference[0] = absolute_number(degrees[i_deg] - (convert * arctan(circle[i].x,circle[i].y * width)));
    }
    else
    {
      difference[0] = difference[1];
    }
  }

  while(i_deg < 14)
  {
    ticks[i_deg] = ticks[i_deg - 1];
    i_deg++;
  }
}

// The Coordinates_line function calculates the coordinates of a line segment
// that runs from the zero coordinate (x:0, y:0) to
// the passed coordinate B. The calculation is performed
// using Bresenham's line algorithm.
// The function is used in drawing watch hands.
//
// The function is used in the Second-hand.cpp,
// Minute-hand.cpp and Hour-hand.cpp files.
void Coordinates_line(std::vector<Coordinates> &line,const Coordinates &B)
{
  line.clear();
  Coordinates temp;
  Coordinates delta = B;
  Coordinates add(1, 0);
  if (B.x < B.y)
  {
    delta.reset(B.y, B.x);
    add.reset(0, 1);
  }

  short d = 2 * delta.y - delta.x;

  do
  {
    if (d < 0)
    {
      temp.x += add.x;
      temp.y += add.y;
      d = d + 2 * delta.y;
    }
    else
    {
      temp.x++;
      temp.y++;
      d = d + 2 * delta.y - 2 * delta.x;
    }
    line.push_back(temp);
  } while (temp != B);
}
