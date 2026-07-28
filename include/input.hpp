#pragma once
#include "Coordinates.hpp"

void block(bool enable);
void clear_buffer();
void get_term_size(Coordinates &size);
bool check_buffer(bool &show_date, bool &color);
