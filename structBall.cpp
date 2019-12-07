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

void Ball::Move()
{
	Point newPos;
	newPos.x = X() + HeadingX();
	newPos.y = Y() + HeadingY();

	//Erase();
	SetPos(newPos);
}
