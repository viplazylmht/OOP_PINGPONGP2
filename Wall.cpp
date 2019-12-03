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
