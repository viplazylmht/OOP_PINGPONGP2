#include "ObjectManager.h"

bool ObjectManager::IsValidPos(shared_ptr<Obstacle> newObstacle)
{
	for (auto obstacle : _obstacles)
	{
		if (obstacle->GetPoint().x == newObstacle->GetPoint().x && (obstacle->GetPoint().y == newObstacle->GetPoint().y))
		{
			return false;
		}
	}
	return true;
}

ObjectManager::ObjectManager()
{
	CreateObstacles();
}

void ObjectManager::CreateObstacles()
{
	//ensure that obstacles is empty
	ClearObject();

	//create foods
	for (int i = 0; i < NUM_FOODS; i++)
	{
		shared_ptr<Obstacle> cur = make_shared<Food>();

		while (!IsValidPos(cur))
		{
			cur->Random();
		}

		_obstacles.push_back(cur);
	}

	_remainFood = NUM_FOODS;

	//create bonuses
	for (int i = 0; i < NUM_BONUS; i++)
	{
		shared_ptr<Obstacle> cur = make_shared<Bonus>();

		while (!IsValidPos(cur))
		{
			cur->Random();
		}

		_obstacles.push_back(cur);

		//if unlucky, create wall before
		if (rand() % 2 == 0)
		{
			shared_ptr<Obstacle> curWall = make_shared<Wall>();

			//minus x and keep y (stand before bonus)
			curWall->SetPoint({ cur->GetPoint().x - 1, cur->GetPoint().y });

			_obstacles.push_back(curWall);
		}
	}

	//create start walls
	for (int i = 0; i < MINIMUM_WALL; i++)
	{
		shared_ptr<Obstacle> cur = make_shared<Wall>();

		while (!IsValidPos(cur))
		{
			cur->Random();
		}

		_obstacles.push_back(cur);
	}
}

void ObjectManager::CreatePuzzle()
{
	while (true)
	{
		//ensure that obstacles is empty
		ClearObject();

		for (int i = 0; i < NUM_PUZZLE_WALL; i++)
		{
			shared_ptr<Obstacle> cur = make_shared<Wall>();

			while (!IsValidPos(cur))
			{
				cur->Random();
			}

			_obstacles.push_back(cur);
		}

		if (CreateFoodPuzzle())
		{
			break;
		}
	}
}

bool ObjectManager::CreateFoodPuzzle()
{
	Ball ball;
	int score;		//fake

	Point farthest;		//farthest point

	while (true)
	{
		farthest.x = 0;		//init
		int i = 1 + rand() % (SCREEN_BOTTOM - SCREEN_TOP - 1);		//start y
		int headingY = rand() % 2;		//random heading y
		if (headingY == 0)
		{
			headingY = -1;
		}

		ball.SetPos({ GAME_BORDER_LEFT + 1, i });
		ball.SetHeadingX(1);
		ball.SetHeadingY(-1);

		//move two step
		ball.Move();
		ball.Move();

		int j = 0;
		while (ball.Pos().x > GAME_BORDER_LEFT + 2)
		{
			j++;
			if (j > 999)
			{
				//may be no way
				return false;
			}
			//check eat
			CheckAndProccessBallCollideWithObstacles(ball, score);

			ball.Move();

			if (ball.Pos().x > farthest.x)
			{
				farthest = ball.Pos();
			}

			//check collide border
			if (ball.Y() < SCREEN_TOP && ball.HeadingY() < 0)
			{
				ball.SetHeadingY(-ball.HeadingY());
			}
			if (ball.Y() > SCREEN_BOTTOM - 2 && ball.HeadingY() > 0)
			{
				ball.SetHeadingY(-ball.HeadingY());
			}
			if (ball.X() >= GAME_BORDER_RIGHT - 1)
			{
				ball.SetHeadingX(-ball.HeadingX());
			}
		}

		if (farthest.x > 2 * (SCREEN_RIGHT - SCREEN_LEFT) / 3)		//ensure that it is hard enough
		{
			break;
		}
	}

	//create food
	shared_ptr<Obstacle> cur = make_shared<Food>();
	//set x to the last
	cur->SetPoint(farthest);
	_obstacles.push_back(cur);

	_remainFood = 1;

	return true;
}

void ObjectManager::DrawObstacles()
{
	for (auto obstacle : _obstacles)
	{
		obstacle->Draw();
	}
}

void ObjectManager::CheckAndProccessBallCollideWithObstacles(Ball& ball, int& score)
{
	int oldScore = score;		//to detect if collide food

	vector<shared_ptr<Obstacle>> trivals;

	bool isHavePriority = false;

	int i = 0;
	for (auto obstacle : _obstacles)
	{
		int nearBallReturn = obstacle->isNearBall(ball);
		if (nearBallReturn == 1)		//priority
		{
			if (obstacle->isCollide(ball))
			{
				obstacle->CollidePoccess(score, ball);

				//update remain food
				if (obstacle->GetText() == '*')
				{
					_remainFood--;
				}
				
				isHavePriority = true;
			}
		}
		else if (nearBallReturn == 2)		//trivals
		{
			trivals.push_back(obstacle);
		}
		i++;
	}

	//check all trivals
	for (auto trival : trivals)
	{
		if (trival->isCollide(ball))
		{
			trival->CollidePoccess(score, ball);

			//update remain food
			if (trival->GetText() == '*')
			{
				_remainFood--;
			}
		}
	}
}

void ObjectManager::ClearObject()
{
	_obstacles.clear();
}

void ObjectManager::CreateNewWall()
{
	shared_ptr<Obstacle> cur = make_shared<Wall>();

	while (!IsValidPos(cur))
	{
		cur->Random();
	}

	_obstacles.push_back(cur);
}
