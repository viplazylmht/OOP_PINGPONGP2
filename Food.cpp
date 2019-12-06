#include "Food.h"

void Food::Random()
{
	Obstacle::Random();
	_text = '0';
}
void Food::CollidePoccess(float& point, Ball& ball)
{
	Obstacle::CollidePoccess(point, ball);
	
	point++;

	_isVisible = false;
}

Food::Food() : Obstacle()
{
	Random();
	_text = FOOD_TEXT;
}
