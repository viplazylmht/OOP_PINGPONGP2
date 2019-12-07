#pragma once

#include <iostream>
#include <vector>
#include "Bonus.h"
#include "Wall.h"
#include "Food.h"
#include "constant.h"

class ObjectManager
{
private:
	vector<shared_ptr<Obstacle>> _obstacles;
	int _remainFood;
	
//get set
public:
	vector<shared_ptr<Obstacle>>& Obstacles() { return _obstacles; }
	int RemainFood() { return _remainFood; }
	void SetRemainFood(int remainFood) { _remainFood = remainFood; }

public:
	ObjectManager();

public:
	void CreateObstacles();

	void CreatePuzzle();

	void DrawObstacles();

	//check if ball collide with obstacle or not. If collide then proccess if needed
	void CheckAndProccessBallCollideWithObstacles(Ball& ball, int& score);

	void ClearObject();

	void CreateNewWall();

private:
	//Return: false if pos is already exit true if not
	bool IsValidPos(shared_ptr<Obstacle> newObstacle);

	//check by let ball in random start pos then check make it go as far as possible if it eat or not
	void CreateFoodPuzzle();
};

