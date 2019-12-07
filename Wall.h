#pragma once

#include "Obstacle.h"

class Wall : public Obstacle
{
public:
	void Random();
	void CollidePoccess(float& point, Ball& ball);
public:
	Wall();
};

