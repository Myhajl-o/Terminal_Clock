#pragma once
#include "Coordinates.hpp"

void setting_term_mode(bool raw_term);
void clear_buffer();
void get_term_size(Coordinates &size);
bool check_buffer(bool &show_date, bool &color);
