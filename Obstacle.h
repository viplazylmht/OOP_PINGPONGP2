#pragma once

#include "Point.h"
#include "structBall.h"

using namespace std;

class Obstacle
{
private:
	char _text;
	Point _point;
	int _color;
	bool _isVisible;

public:
	Obstacle();
	Obstacle(char text, Point point, int color, bool isVisible);
	~Obstacle();

public:
	void Draw();
	virtual void Randome();
	//call firt to collect array obstacle (2 array)
	int isNearBall(Ball ball);
	//check if obstacle in array collide with ball or nor
	bool isCollide(Ball ball);
	//change point base on text + make it invisible + change heading of ball
	void CollidePocess(int& point, Ball& ball);
};