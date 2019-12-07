#pragma once

#include "Obstacle.h"

class Wall : public Obstacle
{
public:
	void Random();
	void CollidePoccess(int& point, Ball& ball);
public:
	Wall();
	Wall(char const& text, Point const& pos, int const& color, bool const& isVisible);
};

