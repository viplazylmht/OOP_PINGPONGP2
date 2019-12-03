#include "Bonus.h"

void Bonus::Random()
{
	Obstacle::Random();

	srand(time(NULL));

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
}
