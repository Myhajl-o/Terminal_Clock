#pragma once

void block(bool enable);

void cursor(bool hide);

void clear_buffer();

void get_term_size(int &x, int &y);

bool check_buffer(bool &show_date);
