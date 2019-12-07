#include "Wall.h"

void Wall::Random()
{
	Obstacle::Random();

	_text = WALL_TEXT;
}
void Wall::CollidePoccess(int& point, Ball& ball)
{
	Obstacle::CollidePoccess(point, ball);
}

Wall::Wall() : Obstacle()
{
	Random();
}

Wall::Wall(char const& text, Point const& pos, int const& color, bool const& isVisible)
	: Obstacle(text, pos, color, isVisible)
{
	_text = text;
	_pos = pos;
	_color = color;
	_isVisible = isVisible;
}
