#include "watch_face.hpp"
#include "Color_object.hpp"
#include "Coordinates.hpp"
#include "math.hpp"
#include "output.h"
#include <vector>

// The calculate_data_circle function calculates all necessary
// data for correctly drawing a circle in the terminal.
//
// The function is used in the draw_watch_face function.
void calculate_data_circle(const Coordinates &size, Coordinates &center, short &radius, std::vector<Coordinates> &circle,const short width)
{
  Coordinate_center(center, size);
  Calculation_radius(radius, 1, center,width);
  Coordinates_circle(circle,radius);
}

// The draw_circle function draws a circle in the terminal window that is
// the base of the clock. In the function, the raw coordinate data of the circle
// is adapted relative to the center of the terminal, and the coordinates are
// reflected to draw the entire circle using the 1/4 circle coordinates.
//
// The function is used in the draw_watch_face function.
void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle,const short width,const Color_object circ,const char*circ_sym)
{
  char space[17];
  short size_sym = filling_space(space,circ_sym,width);

  for (unsigned short i = 0; i < circle.size(); i++)
  {
    output_object(center.x + circle[i].x * width, (center.y - circle[i].y), space, circ.c);
    output_object(center.x + circle[i].x * width, (center.y + circle[i].y), space, circ.c);
    output_object((center.x - circle[i].x * width) - width, (center.y + circle[i].y), space, circ.c);
    output_object((center.x - circle[i].x * width) - width, (center.y - circle[i].y), space, circ.c);
  }

  output_object(center.x, center.y, &space[(width * size_sym) - size_sym], circ.c);
}

// The calculate_data_numbers function calculates all data for outputting the watch face
// into the terminal window (numbers and tick marks).
//
// The function is used in the draw_watch_face function.
void calculate_data_numbers(short &radius, std::vector<Coordinates> &circle_tick, Coordinates *tick,const short width)
{
  radius--;
  Coordinates_circle(circle_tick,radius);
  Coordinate_upgrade(circle_tick,width);
  Coordinate_circle_degrees(tick,circle_tick);
}

// The draw_tick function outputs clock ticks to the terminal window.
// It takes an array of raw coordinates and adapts them relative to the center.
// It also mirrors them because the input coordinates only cover 1/4 of the circle.
//
// This function is used within the watch_face function.
void draw_tick(const Coordinates &center,const Coordinates*tick,const Color_object&t_color,const char*tick_symbol)
{
for (short i = 0; i < 14; i++)
  {
    i += (i == 4 || i == 9);
    output_object(center.x + tick[i].x, center.y - tick[i].y, tick_symbol, t_color.c);
    output_object(center.x + tick[i].x, center.y + tick[i].y, tick_symbol, t_color.c);
    output_object(center.x - tick[i].x - 1, center.y + tick[i].y,tick_symbol, t_color.c);
    output_object(center.x - tick[i].x - 1, center.y - tick[i].y, tick_symbol, t_color.c);
  }
}

// The draw_numbers function outputs the clock numbers to the
// terminal window. In the function, the raw coordinates are adapted relative to
// the center of the terminal, and also reflected to draw all tick marks, rather
// than just those within the 1/4 circle.
//
// The function is used in the draw_watch_face function.
void draw_numbers(const Coordinates &center, const Coordinates *tick, const std::vector<Coordinates> &circle_tick,const short width,const Color_object n_color,const char* const* num_sym,const short*num_shift)
{
  output_object(center.x + tick[4].x + (num_shift[0] - 2), center.y - tick[4].y, num_sym[1], n_color.c);
  output_object(center.x + tick[9].x + (num_shift[1] - 2), center.y - tick[9].y, num_sym[2], n_color.c);
  output_object(center.x + circle_tick[0].y * width + (num_shift[2] - 2), center.y, num_sym[3], n_color.c);

  output_object(center.x + tick[4].x + (num_shift[4] - 2), center.y + tick[4].y, num_sym[5], n_color.c);
  output_object(center.x + tick[9].x + (num_shift[3] - 2), center.y + tick[9].y, num_sym[4], n_color.c);
  output_object(center.x + (num_shift[5] - 2), center.y + circle_tick[0].y, num_sym[6], n_color.c);

  output_object(center.x - tick[4].x - 1 + (num_shift[6] - 2), center.y + tick[4].y, num_sym[7], n_color.c);
  output_object(center.x - tick[9].x - 1 + (num_shift[7] - 2), center.y + tick[9].y, num_sym[8], n_color.c);
  output_object(center.x - circle_tick[0].y * width - 1 + (num_shift[8] - 2), center.y, num_sym[9], n_color.c);

  output_object(center.x - tick[4].x - 1 + (num_shift[10] - 2), center.y - tick[4].y, num_sym[11], n_color.c);
  output_object(center.x - tick[9].x - 1 + (num_shift[9] - 2), center.y - tick[9].y, num_sym[10], n_color.c);
  output_object(center.x + (num_shift[11] - 2), center.y - circle_tick[0].y, num_sym[12], n_color.c);
}

// The draw_watch_face function calculates all data and outputs
// the ready watch face, which is adapted to the size
// of the terminal.
//
// The function is used in the main.cpp file.
void draw_watch_face(const Coordinates &size,const short width,const Color_object*colors,const char*circ_sym,const char* const*num_sym,const short*num_shift)
{
  Coordinates center;
  short radius;
  static std::vector<Coordinates> circle;
  Coordinates tick[14];
  static std::vector<Coordinates> circle_tick;

  calculate_data_circle(size, center, radius, circle,width);
  draw_circle(center, circle,width,colors[0],circ_sym);

  calculate_data_numbers(radius, circle_tick, tick,width);
  draw_tick(center,tick,colors[1],num_sym[0]);
  draw_numbers(center, tick, circle_tick,width,colors[2],num_sym,num_shift);
}
