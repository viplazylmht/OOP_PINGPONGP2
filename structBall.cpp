#include "structBall.h"
struct Ball;

void Ball::Draw()
{
	setTextColor(RED);
	gotoXY(_pos.x, _pos.y); cout << 'o';
}

void Ball::Erase()
{
	txtPlot(_pos.x, _pos.y, 0);
}
