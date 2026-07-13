#include "input.hpp"
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
}

void hide_cursor()
{
	std::cout<<"\033[?25l";
}

void show_cursor()
{
	std::cout<<"\033[?25h";
}

void clear()
{
	tcflush(STDIN_FILENO, TCIFLUSH);
}

bool check_buffer(bool&show_date)
{
	int bytes;
	char c = '1';
	ioctl(STDIN_FILENO, FIONREAD, &bytes);
	if(bytes>0)
	{
		read(STDIN_FILENO, &c, 1);
		
		switch(c)
		{
			case '\x1b':
				char seq[3];
				if(read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1)
				{
					if(seq[0] == '[')
					{
						if(seq[1] == 'B'){ show_date = true;}
						else if(seq[1] == 'A'){ show_date = false;}
					}
				}
			break;
			case 's': show_date = true; break;
			case 'w': show_date = false; break;
			
		}
		clear();	
	}
	return (c == '\n' || c == ' ');
}





