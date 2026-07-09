#pragma once
#include <iostream>
#include <string>
#include <vector>

class Second_hand
{

	std::vector<std::string>second_draw(60);
	
	std::vector<std::string>second_clear(60);



	public:
	
	Second_hand();

	std::string get_second_hands_draw(int current);

	std::string get_second_hands_clear(int current);
	

};
