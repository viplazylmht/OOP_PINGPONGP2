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

	CreateFoodPuzzle();
}

void ObjectManager::CreateFoodPuzzle()
{
	Game game;
	float score;		//fake

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

		game.GetBall().SetPos({ GAME_BORDER_LEFT + 1, i });
		game.GetBall().SetHeadingX(1);
		game.GetBall().SetHeadingY(-1);
		//move two step
		game.MoveBall();
		game.MoveBall();

		while (game.GetBall().Pos().x > GAME_BORDER_LEFT + 2)
		{
			game.GetBall().Draw();

			//check eat
			CheckAndProccessBallCollideWithObstacles(game.GetBall(), score);

			game.MoveBall();

			if (game.GetBall().Pos().x > farthest.x)
			{
				farthest = game.GetBall().Pos();
			}

			int isPlaying = game.gameLogicEatingGame();
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
}

void ObjectManager::DrawObstacles()
{
	for (auto obstacle : _obstacles)
	{
		obstacle->Draw();
	}
}

void ObjectManager::CheckAndProccessBallCollideWithObstacles(Ball& ball, float& score)
{
	float oldScore = score;		//to detect if collide food

	vector<shared_ptr<Obstacle>> trivals;
	bool isHaveTrival = false;

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

				return;
			}
		}
		else if (nearBallReturn == 2)		//trivals
		{
			trivals.push_back(obstacle);
			isHaveTrival = true;
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
