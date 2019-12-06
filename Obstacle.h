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

// Get set
public:
	char GetText() { return _text; };
	Point GetPoint() { return _pos; };
	int GetColor() { return _color; };
	bool IsVisible() { return _isVisible; };

	void SetText(char text) { _text = text; };
	void SetPoint(int x, int y) { _pos.x = x, _pos.y = y; };
	void SetPoint(Point p) { _pos = p; };
	void SetVisible(bool isVisible) { _isVisible = isVisible; };


public:
	void Draw();
	virtual void Random();
	//call firt to collect array obstacle (2 array)
	//Return: 0-not near
	//		  1-near and place in EWSN
	//		  2-near but not place in EWSN
	//call firt to collect array obstacle (2 array)
	int isNearBall(Ball ball);
	//check if obstacle in array collide with ball or nor
	bool isCollide(Ball ball);
	//change point base on text + make it invisible + change heading of ball
	virtual void CollidePoccess(float& point, Ball& ball);
};