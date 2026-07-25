#pragma once
#include "Coordinates.hpp"
#include <vector>

void clear();
void output_string(const int &x, const int &y, const char *s, int color);
void background(const Coordinates &size);
void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle);
void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14], const std::vector<Coordinates> &circle_tick);
void test_function(const std::vector<Coordinates> &circle);
void watch_face(const Coordinates &size);
