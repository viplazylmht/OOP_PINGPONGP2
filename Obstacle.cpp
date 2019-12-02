#include "Obstacle.h"

Obstacle::Obstacle()
{
	_text = ' ';
	_point = {0, 0};
	_color = RED;
	_isVisible = false;
}

Obstacle::Obstacle(char text, Point point, int color, bool isVisible)
{
	_text = text;
	_point = point;
	_color = color;
	_isVisible = isVisible; 
}

Obstacle::~Obstacle()
{
}

void Obstacle::Draw()
{
}

void Obstacle::Randome()
{
}

int Obstacle::isNearBall(Ball ball)
{
	return 0;
}

bool Obstacle::isCollide(Ball ball)
{
	return false;
}

void Obstacle::CollidePocess(int& point, Ball& ball)
{
}
