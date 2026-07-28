#pragma once
#include "Coordinates.hpp"
#include <vector>

void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle);
void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14], const std::vector<Coordinates> &circle_tick);
void watch_face(const Coordinates &size);
