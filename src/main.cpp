#include "game.hpp"

int main()
{
    int a;
	Game game;
	return game.run();


	int layer_w	 = 400;
	int screen_w = 320;
	int pos_x = 450;

//	( (400  - (320 mod 400)) / 400) * 400
	int init_x1	=  ( pos_x % layer_w );
	int end_x1	= layer_w - init_x1;

	int init_x2	=  0;
	int end_x2	= init_x1;

	printf("coisa1: %d - %d\n", init_x1, end_x1);
	printf("coisa2: %d - %d\n", init_x2, end_x2);
	return 0;
}
