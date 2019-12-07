#pragma once

#include "Obstacle.h"

class Food : public Obstacle
{
public:
	void Random();
	void CollidePoccess(int& point, Ball& ball);

public:
	Food();
	Food(char const& text, Point const& pos, int const& color, bool const& isVisible);
};

