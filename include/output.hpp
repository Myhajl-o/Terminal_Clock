#pragma once
#include "Coordinates.hpp"
#include <vector>

void clear();
void output_two_char(const int &x, int &y, const char s[], int color);
void output_char(const int &x, const int &y, char c, int color);
void background(const int &x, const int &y);
void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle);
void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14], const std::vector<Coordinates> &circle_tick);
void test_function(const std::vector<Coordinates> &circle);
// void test_function1(const Coordinates ass);
void watch_face(const int &size_x, const int &size_y);
