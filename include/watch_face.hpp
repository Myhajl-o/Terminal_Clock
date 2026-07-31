#pragma once
#include "Coordinates.hpp"
#include <vector>

void calculate_data_circle(const Coordinates &size, Coordinates &center, short &radius, std::vector<Coordinates> &circle);
void draw_circle(const Coordinates &center, const std::vector<Coordinates> &circle);
void calculate_data_numbers(short &radius, std::vector<Coordinates> &circle_tick, Coordinates (&tick)[14]);
void draw_numbers(const Coordinates &center, const Coordinates (&tick)[14], const std::vector<Coordinates> &circle_tick);
void draw_watch_face(const Coordinates &size);
