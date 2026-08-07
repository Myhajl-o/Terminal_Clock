#include "watch_face.hpp"
#include "Color_object.hpp"
#include "Coordinates.hpp"
#include "math.hpp"
#include "output.hpp"
#include <vector>

// The calculate_data_circle function calculates all necessary
// data for correctly drawing a circle in the terminal.
//
// The function returns nothing, and passes the result
// into a variable by reference.
//
// The function is used in the draw_watch_face function.
void calculate_data_circle(const Coordinates &size, Coordinates &center, short &radius, std::vector<Coordinates> &circle,const short width)
{
  Coordinate_center(center, size);
  Calculation_radius(radius, 1, center,width);
  Coordinates_circle(radius, circle);
}

// The draw_circle function draws a circle in the terminal window that is
// the base of the clock. In the function, the raw coordinate data of the circle
// is adapted relative to the center of the terminal, and the coordinates are
// reflected to draw the entire circle using the 1/4 circle coordinates.
//
// The function returns nothing; it only receives constant data.
//
// The function is used in the draw_watch_face function.
void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle,const short width,const Color_object circ,char*circ_sym)
{
  short size_sym = circ_sym[5];
  char space[17];
  short j = 0;

  for(short i = 0; i < (width * size_sym); i++)
  {
    if(j == size_sym) j = 0;
    space[i] = circ_sym[j];
    j++;
  }

  space[width * size_sym] = '\0';

  for (unsigned short i = 0; i < circle.size(); i++)
  {
    output_symbols(center.x + circle[i].x * width, (center.y - circle[i].y), space, circ);
    output_symbols(center.x + circle[i].x * width, (center.y + circle[i].y), space, circ);
    output_symbols((center.x - circle[i].x * width) - width, (center.y + circle[i].y), space, circ);
    output_symbols((center.x - circle[i].x * width) - width, (center.y - circle[i].y), space, circ);
  }

  output_symbols(center.x, center.y, &space[(width * size_sym) - size_sym], circ);
}

// The calculate_data_numbers function calculates all data for outputting the watch face
// into the terminal window (numbers and tick marks).
//
// The function returns nothing, but writes the result into the variables passed
// by reference.
//
// The function is used in the draw_watch_face function.
void calculate_data_numbers(short &radius, std::vector<Coordinates> &circle_tick, Coordinates (&tick)[14],const short width)
{
  radius--;
  Coordinates_circle(radius, circle_tick);
  Coordinate_upgrade(circle_tick,width);
  for (short i = 0; i < 14; i++)
  {
    Coordinate_degree((i + 1) * 6, tick[i], circle_tick);
  }
}

// The draw_numbers function outputs the clock numbers and tick marks to the
// terminal window. In the function, the raw coordinates are adapted relative to
// the center of the terminal, and also reflected to draw all tick marks, rather
// than just those within the 1/4 circle.
//
// The function returns nothing, and only takes constant data.
//
// The function is used in the draw_watch_face function.
void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14], const std::vector<Coordinates> &circle_tick,const short width,const Color_object num,char** num_sym,const short*num_shift)
{
  for (short i = 0; i < 14; i++)
  {
    i += (i == 4 || i == 9);
    output_symbols(center.x + tick[i].x, center.y - tick[i].y, num_sym[0], num);
    output_symbols(center.x + tick[i].x, center.y + tick[i].y, num_sym[0], num);
    output_symbols(center.x - tick[i].x - 1, center.y + tick[i].y, num_sym[0], num);
    output_symbols(center.x - tick[i].x - 1, center.y - tick[i].y, num_sym[0], num);
  }
  output_symbols(center.x + tick[4].x + (num_shift[0] - 2), center.y - tick[4].y, num_sym[1], num);
  output_symbols(center.x + tick[9].x + (num_shift[1] - 2), center.y - tick[9].y, num_sym[2], num);
  output_symbols(center.x + circle_tick[0].y * width + (num_shift[2] - 2), center.y, num_sym[3], num);

  output_symbols(center.x + tick[4].x + (num_shift[4] - 2), center.y + tick[4].y, num_sym[5], num);
  output_symbols(center.x + tick[9].x + (num_shift[3] - 2), center.y + tick[9].y, num_sym[4], num);
  output_symbols(center.x + (num_shift[5] - 2), center.y + circle_tick[0].y, num_sym[6], num);

  output_symbols(center.x - tick[4].x - 1 + (num_shift[6] - 2), center.y + tick[4].y, num_sym[7], num);
  output_symbols(center.x - tick[9].x - 1 + (num_shift[7] - 2), center.y + tick[9].y, num_sym[8], num);
  output_symbols(center.x - circle_tick[0].y * width - 1 + (num_shift[8] - 2), center.y, num_sym[9], num);

  output_symbols(center.x - tick[4].x - 1 + (num_shift[10] - 2), center.y - tick[4].y, num_sym[11], num);
  output_symbols(center.x - tick[9].x - 1 + (num_shift[9] - 2), center.y - tick[9].y, num_sym[10], num);
  output_symbols(center.x + (num_shift[11] - 2), center.y - circle_tick[0].y, num_sym[12], num);
}

// The draw_watch_face function calculates all data and outputs
// the ready watch face, which is adapted to the size
// of the terminal.
//
// The function returns nothing, and only takes constant data.
//
// The function is used in the main.cpp file.
void draw_watch_face(const Coordinates &size,const short width, const Color_object circ,const Color_object num,char*circ_sym,char**num_sym,const short*num_shift)
{
  Coordinates center;
  short radius;
  std::vector<Coordinates> circle;
  Coordinates tick[14];
  std::vector<Coordinates> circle_tick;

  calculate_data_circle(size, center, radius, circle,width);
  draw_circle(center, circle,width,circ,circ_sym);

  calculate_data_numbers(radius, circle_tick, tick,width);
  draw_numbers(center, tick, circle_tick,width,num,num_sym,num_shift);
}
