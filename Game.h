#pragma once

#include "structBall.h"
#include "structPad.h"

class Game
{
private:
	Ball ball;
	Pad  PlayersPad, computersPad;
	int keypressed, isPlayer2, playersScore, computersScore;
	float count;

public:
	Game();
	~Game();
public:
	Ball& GetBall();
	Pad& GetPlayerPad();
	Pad& GetComputerPad();
	int getCount();
	int getPlayersScore();
	int getComputersScore();
	void setIsPlayer2(int data);
	int getIsPlayer2();

	void MoveBall();
	void initGame();
	void Keypressed();
	void gameLogic();
	void gameLogicEatingGame();
	void removeBall();
	void removePads();
	void DrawPads();
	void displayYouMissed();


	void clrscr();
	void box(int x, int y, int sx, int sy, char text_[]);
	void clrbox(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char bkcol);

};


