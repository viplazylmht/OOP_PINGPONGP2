#pragma once

#include "Obstacle.h"

class Food : public Obstacle
{
public:
	void Random();
	void CollidePoccess(float& point, Ball& ball);

public:
	Food();
};

