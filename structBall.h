#pragma once

#include "Point.h"
#include "functionConsole.h"
#include "constant.h"

class Ball
{
private:
	Point _pos;
	int _headingX;
	int _headingY;

public:
	Point Pos() { return _pos; }
	int X() { return _pos.x; }
	int Y() { return _pos.y; }
	void SetPos(int x, int y) { _pos.x = x; _pos.y = y; }
	void SetPos(Point point) { _pos = point; };


	int HeadingX() { return _headingX; }
	void SetHeadingX(int x) { _headingX = x; }

	int HeadingY() { return _headingY; }
	void SetHeadingY(int y) { _headingY = y; }

	void Draw();
	void Erase();
};