#pragma once
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>


void block(bool enable);

void hide_cursor();

void show_cursor();

bool check_buffer();

bool exit();
