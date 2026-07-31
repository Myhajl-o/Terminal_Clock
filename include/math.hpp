#ifndef MATH_HPP
#define MATH_HPP

#include "Coordinates.hpp"
#include <vector>

void Coordinate_center(Coordinates &center, const Coordinates &size);
void Calculation_radius(short &radius, short backdown, const Coordinates &center);
void Coordinates_circle(const short &radius, std::vector<Coordinates> &circle);
void Coordinate_upgrade(std::vector<Coordinates> &circle);
void Coordinate_degree(short degree, Coordinates &tick_element, const std::vector<Coordinates> &circle);
void Coordinates_line(const Coordinates &B, std::vector<Coordinates> &line);

#endif
