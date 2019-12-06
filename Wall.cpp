#include "Wall.h"

void Wall::Random()
{
	Obstacle::Random();

	_text = WALL_TEXT;
}
void Wall::CollidePoccess(float& point, Ball& ball)
{
	Obstacle::CollidePoccess(point, ball);
}

Wall::Wall() : Obstacle()
{
	Random();
}
