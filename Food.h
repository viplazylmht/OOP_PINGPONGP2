#pragma once

#include "Obstacle.h"

class Food : public Obstacle
{
public:
	void Random();
	void CollidePoccess(int& point, Ball& ball);
};

