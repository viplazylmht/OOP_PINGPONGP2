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

	_isVisible = false;
}

Food::Food() : Obstacle()
{
	Random();
	_text = FOOD_TEXT;
}

Food::Food(char const& text, Point const& pos, int const& color, bool const& isVisible)
	: Obstacle(text, pos, color, isVisible)
{
	_text = text;
	_pos = pos;
	_color = color;
	_isVisible = isVisible;
}
