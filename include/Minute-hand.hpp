#pragma once
#include <iostream>
#include <string>
#include <vector>

class Minute_hand
{

	std::vector<std::string>minute_draw;

	std::vector<std::string>minute_clear;

	public:
	Minute_hand();

	std::string get_minute_hand_draw(int current);

	std::string get_minute_hand_clear(int current);	
	
};
