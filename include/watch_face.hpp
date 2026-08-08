#ifndef WATCH_FACE_HPP
#define WATCH_FACE_HPP

#include "Coordinates.hpp"
#include "Color_object.hpp"
#include <vector>

void calculate_data_circle(const Coordinates &size, Coordinates &center, short &radius, std::vector<Coordinates> &circle,const short width);
void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle,const short width,const Color_object circ,const char*circ_sym);
void calculate_data_numbers(short &radius, std::vector<Coordinates> &circle_tick, Coordinates *tick,const short width);
void draw_tick(const Coordinates &center,const Coordinates*tick,const Color_object&t_color,const char*tick_symbols);
void draw_numbers(const Coordinates &center, const Coordinates *tick, const std::vector<Coordinates> &circle_tick,const short width,const Color_object n_color,const char* const*num_sym,const short*num_shift);
void draw_watch_face(const Coordinates &size,const short width,const Color_object*colors,const char*circ_sym,const char* const*num_sym,const short*num_shift);

#endif
