#pragma once

#include "structBall.h"
#include "structPad.h"
#include "SaveGame.h"
#include "ObjectManager.h"

class Game
{
private:
	Ball ball;
	Pad  PlayersPad, computersPad;
	int keypressed, isPlayer2, playersScore, computersScore;
	float count;
	ObjectManager _obstacles;

	string _name;

public:
	Game();
	~Game();
public:
	Ball& GetBall();
	Pad& GetPlayerPad();
	Pad& GetComputerPad();
	int getCount();
	int& getPlayersScore();
	int getComputersScore();
	void setIsPlayer2(int data);
	int getIsPlayer2();
	ObjectManager& Obstacles();

	void MoveBall();
	void initGame();
	//return 1 if ask new game (use to draw new background
	int Keypressed();
	void gameLogic();
	//Return: false if lose, true if not
	bool gameLogicEatingGame();
	void removeBall();
	void removePads();
	void DrawPads();
	void displayYouMissed();
	void displayYouWin();

	void SaveRanking(string);
	void SaveGameState(string);
	void PauseGame();
	void DisplaySavedGame();
	void DisplayLoadedGame();
	void DisplayEnterName();

	void clrscr();
	void box(int x, int y, int sx, int sy, char text_[]);
	void clrbox(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char bkcol);

};


