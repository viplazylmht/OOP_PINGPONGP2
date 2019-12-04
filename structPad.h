#pragma once
#include "functionConsole.h"
#include "Point.h"
#include "constant.h"
#include "functionConsole.h"

class Pad {
private:

	Point _head;
	int _length;
	bool _isVisible;

public:
	Pad();
	Pad(Point head, int len);
	Pad(int x, int y, int len);

	Point GetPoint() { return _head; };
	int HeadX() { return _head.x; };
	int HeadY() { return _head.y; };
	int Length() { return _length; };
	bool isVisible() { return _isVisible; };

	void SetPoint(Point head);
	void SetPoint(int x, int y);
	void SetLength(int len);
	void SetVisible(bool isVisible);

	void Erase();
	void Draw(int color);

	void MoveUp();
	void MoveDown();
};

