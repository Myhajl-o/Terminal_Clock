#include "input_block.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>


void block(bool enable)
{
	static struct termios oldt, newt;
	static bool initialized = false;
	if(!initialized)
	{
		if(tcgetattr(STDIN_FILENO, &oldt) < 0)
		{
			return;
		}
	initialized = true;
	}
	
	if(enable)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
	else
	{
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	}
	hide_cursor();
}

void hide_cursor()
{
	std::cout<<"\033[?25l";
}

void show_cursor()
{
	std::cout<<"\033[?25h";
}

bool check_buffer()
{
	int bytes;
	ioctl(STDIN_FILENO, FIONREAD, &bytes);
	if(bytes>0)
	{
		char c;
		read(STDIN_FILENO, &c, 1);	
		return (c == '\n' || c == ' ');
	}
	return false;
}


bool exit()
{
	if(check_buffer())
	{
		block(true);
		tcflush(STDIN_FILENO, TCIFLUSH);
		show_cursor();
		return true;
	}
	tcflush(STDIN_FILENO, TCIFLUSH);
	return false;
}




