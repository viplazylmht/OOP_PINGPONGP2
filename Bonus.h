#pragma once

#include "Obstacle.h"

class Bonus : public Obstacle
{
public:
	void Random();
	void CollidePoccess(int& point, Ball& ball);

public:
	Bonus();
};

