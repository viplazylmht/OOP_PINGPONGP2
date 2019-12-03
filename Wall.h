#pragma once

#include "Obstacle.h"

class Wall : public Obstacle
{
public:
	void Random();
	void CollidePoccess(int& point, Ball& ball);
};

