#include "structPad.h"

struct Pad;

Pad::Pad()
{
	_head = { 0, 0 };
	_length = PAD_LENGTH;
	_isVisible = false;
}

Pad::Pad(Point head, int len)
{
	_head = head;
	_length = len;
	_isVisible = true;
}

Pad::Pad(int x, int y, int len)
{
	_head = { x, y };
	_length = len;
	_isVisible = true;
}

void Pad::SetPoint(Point head)
{
	_head = head;
}

void Pad::SetPoint(int x, int y)
{
	_head = { x, y };
}

void Pad::SetLength(int len)
{
	_length = len;
}

void Pad::SetVisible(bool isVisible)
{
	_isVisible = isVisible;
}

void Pad::Erase()
{
	txtLine(_head.x, _head.y, _head.x, _head.y + _length, 0);
}

void Pad::Draw(int color)
{
	if (_isVisible) txtLine(_head.x, _head.y, _head.x, _head.y + _length, color);
}

void Pad::MoveUp()
{
	Erase();
	if (_head.y <= GAME_BORDER_TOP + 1) _head.y = GAME_BORDER_TOP + 1;
	else _head.y -= 1;
}

void Pad::MoveDown()
{
	Erase();
	if ( _head.y + _length >= GAME_BORDER_BOTTOM - 1) _head.y = GAME_BORDER_BOTTOM - _length - 1;
	else _head.y += 1;
}


