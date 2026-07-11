#pragma once
#include <iostream>
#include <string>
#include <vector>


class Hour_hand
{

	std::vector<std::string>hour_draw;

	std::vector<std::string>hour_clear;

	
	public:

	Hour_hand();

	std::string get_hour_hand_draw(int current);

	std::string get_hour_hand_clear(int current);

};
