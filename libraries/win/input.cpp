#include "input.hpp"
#include <iostream>
#include <windows.h>

void block(bool state)
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	
	if(state)
	{
		mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
	}
	else
	{
		mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
	}
	SetConsoleMode(hStdin, mode);
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
	HANDLE hStdin = GetStdHandle(STD_IINPUT_HANDLE);
	FlushConsoleInputBuffer(hStdin);
}

bool check_buffer(bool&show_date)
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	unsigned char c;
	DWORD read_chars;
	ReadConsoleA(hStdin, &c, 1, &read_chars, NULL);
	if(c == 224 || c == 0)
	{
		ReadConsoleA(hStdin, &c, 1, &read_chars, NULL);
		if(c == 80)
		{
			show_date = true;
		}
		else if(c == 72)
		{
			show_date = false;
		}
	}
	clear();
	if(c == 's')
	{
		show_date = true;
	}
	else if(c == 'w')
	{
		show_date = false;
	}
	return (c == '\n' || c == ' ');
}





