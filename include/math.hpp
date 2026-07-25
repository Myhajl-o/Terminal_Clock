#pragma once
#include "Coordinates.hpp"
#include <vector>

void Coordinate_center(Coordinates &center, const Coordinates &size);
void Radius(int &radius, int backdown, const Coordinates &center);
void Coordinates_circle(const int &radius, std::vector<Coordinates> &circle);
void Coordinate_upgrade(std::vector<Coordinates> &circle);
void Degree(int degree, Coordinates &tick_element, const std::vector<Coordinates> &circle);
void Calculation_degrees(Coordinates (&degrees)[14], const std::vector<Coordinates> &circle);
void Coordinates_line(const Coordinates &B, std::vector<Coordinates> &line);
