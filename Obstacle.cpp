#include "Obstacle.h"

Obstacle::Obstacle()
{
	_text = '0';
	Random();
	_isVisible = true;
}

Obstacle::Obstacle(char text, Point pos, int color, bool isVisible)
{
	_text = text;
	_pos = pos;
	_color = color;
	_isVisible = isVisible;
}

Obstacle::~Obstacle()
{
}

void Obstacle::Draw()
{
	if (_isVisible)
	{
		//draw
		gotoXY(_pos.x, _pos.y);
		cout << _text;
	}
}

void Obstacle::Random()
{
	srand(time(NULL));
	
	_color = rand() % 14 + 1;		//rand int (1-15)
	
	int screenWidth = SCREEN_RIGHT - SCREEN_LEFT; 
	int screenHeight = SCREEN_TOP - SCREEN_BOTTOM;

	_pos.x = screenWidth / 2 + rand() % (screenWidth / 2);		//ensure that pos of obstacle is at least haft of screen
	_pos.y = screenHeight / 2 + rand() % (screenHeight / 2);		//ensure that pos of obstacle is at least haft of screen
}

int Obstacle::isNearBall(Ball ball)
{
	if (!_isVisible)
	{
		return 0;
	}
	int dentalX = abs(ball.Pos().y - _pos.y);
	int dentalY = abs(ball.Pos().x - _pos.x);
	if ((ball.Pos().x == _pos.x &&  dentalY== 1)
		|| (ball.Pos().y == _pos.y &&  dentalX== 1))
	{
		return 1;
	}

	if (dentalX == 1 && dentalY == 1)
	{
		return 2;
	}
	return 0;
}

bool Obstacle::isCollide(Ball ball)
{
	int nextX = ball.Pos().x + ball.HeadingX();
	int nextY = ball.Pos().y + ball.HeadingY();

	if (nextX == _pos.x && nextY == _pos.y)
	{
		return true;
	}
	return false;
}

void Obstacle::CollidePoccess(int& point, Ball& ball)
{
	//proccess ball
	//if collide with corner
	if (ball.X() + ball.HeadingX() == _pos.x && ball.Y() + ball.HeadingY() == _pos.y)
	{
		ball.SetHeadingX(-ball.HeadingX());
		ball.SetHeadingY(-ball.HeadingY());
	}
	//if collide edge x
	else if (ball.X() + ball.HeadingX() == _pos.x)
	{
		ball.SetHeadingX(-ball.HeadingX());
	}
	//if collide edge y
	else if (ball.Y() + ball.HeadingY() == _pos.x)
	{
		ball.SetHeadingY(-ball.HeadingY());
	}
}
