#include "Food.h"

void Food::Random()
{
	Obstacle::Random();
	_text = '0';
}

void Food::CollidePoccess(int& point, Ball& ball)
{
	Obstacle::CollidePoccess(point, ball);
	
	point++;
}
