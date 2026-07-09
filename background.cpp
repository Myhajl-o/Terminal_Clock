#include <iostream>
#include <string>
#include "background.hpp"


void draw_circle(int row1, int column1, int column2, int space, int top)
{
	if(top == 1)
	{
		std::string spaces(space,' ');
		std::cout<<"\033["<<row1<<";"<<column1<<"H\033[40m"<<spaces<<"\033[47m"<<std::flush;	
	}
	else if(top == 0)
	{
		std::string spaces(space,' ');
		std::cout<<"\033["<<row1<<";"<<column1<<"H\033[40m"<<spaces<<"\033[47m\033["<<row1<<";"<<column2<<"H\033[40m"<<spaces<<"\033[47m"<<std::flush;
	}
}

void background_draw()
{
	std::string background(8161,' ');
	std::cout<<"\033[47m"<<background<<std::flush;
	
	
	draw_circle(2,72,0,29,1);
	draw_circle(3,66,0,41,1);
	draw_circle(4,61,0,51,1);
	draw_circle(5,57,101,15,0);
	draw_circle(6,54,107,12,0);
	draw_circle(7,52,111,10,0);
	draw_circle(8,50,114,9,0);
	draw_circle(9,48,117,7,0);
	draw_circle(10,47,119,7,0);
	draw_circle(11,46,121,6,0);
	draw_circle(12,44,123,6,0);
	draw_circle(13,43,124,6,0);
	draw_circle(14,42,125,6,0);
	draw_circle(15,42,126,5,0);
	draw_circle(16,41,127,5,0);
	draw_circle(17,40,127,6,0);
	draw_circle(18,40,128,5,0);
	draw_circle(19,39,129,5,0);
	draw_circle(20,39,129,5,0);
	draw_circle(21,39,129,5,0);
	draw_circle(22,38,130,5,0);
	draw_circle(23,38,130,5,0);
	draw_circle(24,38,130,5,0);
	draw_circle(24,86,0,1,1);
	draw_circle(25,38,130,5,0);
	draw_circle(26,38,130,5,0);
	draw_circle(27,39,129,5,0);
	draw_circle(28,39,129,5,0);
	draw_circle(29,39,129,5,0);
	draw_circle(30,40,128,5,0);
	draw_circle(31,40,127,6,0);
	draw_circle(32,41,127,5,0);
	draw_circle(33,42,126,5,0);
	draw_circle(34,42,125,6,0);
	draw_circle(35,43,124,6,0);
	draw_circle(36,44,122,6,0);
	draw_circle(37,46,120,6,0);
	draw_circle(38,47,118,7,0);
	draw_circle(39,48,116,8,0);
	draw_circle(40,50,113,9,0);
	draw_circle(41,52,109,10,0);
	draw_circle(42,54,105,12,0);
	draw_circle(43,57,101,15,0);
	draw_circle(44,61,0,51,1);
	draw_circle(45,66,0,41,1);
	draw_circle(46,72,0,29,1);	


	std::cout<<"\033[30m\033[6;70H.\033[6;75H.\033[6;80H.\033[6;86H12\033[6;92H.\033[6;97H.\033[6;102H."<<std::flush;
	std::cout<<"\033[7;66H.\033[7;106H."<<std::flush;
	std::cout<<"\033[8;62H11\033[8;109H1"<<std::flush;
	std::cout<<"\033[9;59H.\033[9;113H."<<std::flush;
	std::cout<<"\033[11;55H.\033[11;117H."<<std::flush;
	std::cout<<"\033[12;52H.\033[12;120H."<<std::flush;
	std::cout<<"\033[13;50H.\033[13;122H."<<std::flush;
	std::cout<<"\033[15;49H10\033[15;123H2"<<std::flush;
	std::cout<<"\033[17;48H.\033[17;124H."<<std::flush;
	std::cout<<"\033[19;47H.\033[19;125H."<<std::flush;
	std::cout<<"\033[20;46H.\033[20;126H."<<std::flush;
	std::cout<<"\033[22;45H.\033[22;127H."<<std::flush;
	std::cout<<"\033[24;44H9\033[24;128H3"<<std::flush;
	std::cout<<"\033[26;45H.\033[26;127H."<<std::flush;
	std::cout<<"\033[28;45H.\033[28;127H."<<std::flush;
	std::cout<<"\033[29;46H.\033[29;126H."<<std::flush;
	std::cout<<"\033[31;48H.\033[31;125H."<<std::flush;
	std::cout<<"\033[33;49H8\033[33;123H4"<<std::flush;
	std::cout<<"\033[35;50H.\033[35;121H."<<std::flush;
	std::cout<<"\033[36;52H.\033[36;119H."<<std::flush;
	std::cout<<"\033[38;56H.\033[38;115H."<<std::flush;
	std::cout<<"\033[39;59H.\033[39;112H."<<std::flush;
	std::cout<<"\033[40;63H7\033[40;108H5"<<std::flush;
	std::cout<<"\033[41;66H.\033[41;105H."<<std::flush;
	std::cout<<"\033[42;70H.\033[42;75H.\033[42;80H.\033[42;86H6\033[42;91H.\033[42;96H.\033[42;101H."<<std::flush;
}
