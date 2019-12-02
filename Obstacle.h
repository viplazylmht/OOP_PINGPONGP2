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

// Get set
public:
	char GetText() { return _text; };
	Point GetPoint() { return _point; };
	int GetColor() { return _color; };
	bool IsVisible() { return _isVisible; };

	void SetText(char text) { _text = text; };
	void SetPoint(int x, int y) { _point.x = x, _point.y = y; };
	void SetPoint(Point p) { _point = p; };
	void SetVisible(bool isVisible) { _isVisible = isVisible; };


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