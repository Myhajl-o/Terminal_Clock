#include "date.hpp"
#include <iostream>
#include <string>
#include <iomanip>

void show_window_date(bool show,int day, int month, int year)
{
	if(show)
	{
		std::cout<<"\033[40m\033[1;128H                                \033[47m";
		std::cout<<"\033[40m\033[37m\033[2;128H          DD//MM//YYYY          \033[47m\033[30m";
		std::cout<<"\033[40m\033[3;128H                                \033[47m";
		std::cout<<"\033[40m\033[4;128H  \033[47m        \033[40m  \033[47m        \033[40m  \033[47m        \033[40m  \033[47m";
		std::cout<<"\033[40m\033[5;128H  \033[47m   "<<std::setfill('0')<<std::setw(2)<<day<<"   \033[40m  \033[47m   "<<std::setfill('0')<<std::setw(2)<<month<<"   \033[40m  \033[47m  "<<std::setfill('0')<<std::setw(4)<<year<<"  \033[40m  \033[47m";
		std::cout<<"\033[40m\033[6;128H  \033[47m        \033[40m  \033[47m        \033[40m  \033[47m        \033[40m  \033[47m";
		std::cout<<"\033[40m\033[7;128H                                \033[47m";
		std::cout<<"\033[40m\033[8;128H                                \033[47m";
	}
	else
	{
		std::cout<<"\033[47m\033[1;128H                                ";
		std::cout<<"\033[47m\033[2;128H                                ";
		std::cout<<"\033[47m\033[3;128H                                ";
		std::cout<<"\033[47m\033[4;128H                                ";
		std::cout<<"\033[47m\033[5;128H                                ";
		std::cout<<"\033[47m\033[6;128H                                ";
		std::cout<<"\033[47m\033[7;128H                                ";
		std::cout<<"\033[47m\033[8;128H                                ";
	}
}
