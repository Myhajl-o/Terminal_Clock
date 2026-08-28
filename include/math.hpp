#ifndef MATH_HPP
#define MATH_HPP

#include "Coordinates.hpp"
#include <vector>

inline float absolute_number(float number);
double simple_pow(double num,short power);
float arctan(short a,short b);
void Coordinate_center(Coordinates &center, const Coordinates &size);
void Calculation_radius(short &radius, short backdown, const Coordinates &center,const short width);
void Coordinates_circle(std::vector<Coordinates> &circle,const short radius);
void Coordinate_upgrade(std::vector<Coordinates> &circle,const short width);
void Coordinate_degree(Coordinates &tick_element,const short degree,const std::vector<Coordinates> &circle,const short width);
void Coordinate_circle_degrees(Coordinates *ticks,const std::vector<Coordinates>&circle,const short width);
void Coordinates_line(std::vector<Coordinates> &line,const Coordinates &B);

#endif
