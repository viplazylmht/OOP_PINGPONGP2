#include "Bonus.h"

void Bonus::Random()
{
	Obstacle::Random();

	int type = rand() % 2;		//0: x2		1:x0.5

	if (type == 0)
	{
		_text = BONUS_X2_TEXT;
	}
	if (type == 1)
	{
		_text = MINUS_TEXT;
	}
}
void Bonus::CollidePoccess(int& point, Ball& ball)
{
	Obstacle::CollidePoccess(point, ball);

	if (_text == BONUS_X2_TEXT)
	{
		point *= 2;
	}
	if (_text == MINUS_TEXT)
	{
		point /= 2;
	}

	_isVisible = false;
}

Bonus::Bonus() : Obstacle()
{
	Random();
}

Bonus::Bonus(char const& text, Point const& pos, int const& color, bool const& isVisible)
	: Obstacle(text, pos, color, isVisible)
{
	_text = text;
	_pos = pos;
	_color = color;
	_isVisible = isVisible;
}
