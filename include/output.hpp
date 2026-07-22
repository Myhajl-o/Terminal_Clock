#pragma once
#include "Coordinates.hpp"
#include <vector>

void clear();
void output_space(const int &x, int &y, int color);
void output_char(const int &x, const int &y, char c);
void background(const int &x, const int &y);
void draw_circle(const Coordinates &center,
                 const std::vector<Coordinates> &circle);
void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14],
                  const std::vector<Coordinates> &circle_tick);
void test_function(const std::vector<Coordinates> &circle,
                   const std::vector<Coordinates> &circle_tick,
                   const Coordinates (&tick)[14]);

void watch_face(const int &size_x, const int &size_y);
