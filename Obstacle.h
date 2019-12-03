#pragma once

#include "Point.h"
#include "structBall.h"
#include "constant.h"
#include "functionConsole.h"
#include <time.h>
#include <math.h>

using namespace std;

class Obstacle
{
protected:
	char _text;
	Point _pos;
	int _color;
	bool _isVisible;

public:
	Obstacle();
	Obstacle(char text, Point pos, int color, bool isVisible);
	~Obstacle();

public:
	void Draw();
	virtual void Random();
	//call firt to collect array obstacle (2 array)
	//Return: 0-not near
	//		  1-near and place in EWSN
	//		  2-near but not place in EWSN
	int isNearBall(Ball ball);
	//check if obstacle in array collide with ball or nor
	bool isCollide(Ball ball);
	//change point base on text + make it invisible + change heading of ball
	virtual void CollidePoccess(int& point, Ball& ball);
};