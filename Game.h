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
	//return 1 if ask new game (use to draw new background
	int Keypressed();
	void gameLogic();
	//isShowPanel: true if lose then show you miss, false if not
	//we need it to create puzzle but when create, should not show lose panel
	//Return: false if lose, true if not
	bool gameLogicEatingGame();
	void removeBall();
	void removePads();
	void DrawPads();
	void displayYouMissed();
	void displayYouWin();


	void clrscr();
	void box(int x, int y, int sx, int sy, char text_[]);
	void clrbox(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char bkcol);

};


