#ifndef WATCH_FACE_HPP
#define WATCH_FACE_HPP

#include "Coordinates.hpp"
#include "Color_object.hpp"
#include <vector>

void calculate_data_circle(const Coordinates &size, Coordinates &center, short &radius, std::vector<Coordinates> &circle,const short width);
void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle,const short width,const Color_object circ,char*circ_sym);
void calculate_data_numbers(short &radius, std::vector<Coordinates> &circle_tick, Coordinates (&tick)[14],const short width);
void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14], const std::vector<Coordinates> &circle_tick,const short width,const Color_object num,char**num_sym,const short*num_shift);
void draw_watch_face(const Coordinates &size,const short width,const Color_object circ,const Color_object num,char*circ_sym,char**num_sym,const short*num_shift);

#endif
