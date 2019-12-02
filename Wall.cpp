#include "Wall.h"

void Wall::Random()
{
	Obstacle::Random();

	_text = WALL_TEXT;
}
