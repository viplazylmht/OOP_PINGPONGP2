#include "Game.h"
#include "structBall.h"
#include "structPad.h"
#include "windows.h"
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "time.h"
#include "iostream"
#include "math.h"
#include "fstream"
#include "constant.h"
#include "functionConsole.h"

using namespace std;



Game::Game()
{
	PlayersPad = Pad(0, 0, PAD_LENGTH);
	computersPad = Pad(0, 0, PAD_LENGTH);
	isPlayer2 = 1;

	_name = "player";
}
Game::~Game()
{
}

//
// INPUT:
// OUTPUT:
// xoa ball cu
void Game::removeBall()
{
	ball.Erase();
}

void Game::removePads()
{
	PlayersPad.Erase();
	computersPad.Erase();
}

void Game::DrawPads()
{
	PlayersPad.Draw(DARK_BLUE);
	computersPad.Draw(DARK_RED);
}

//
// INPUT:
// OUTPUT:
// Kiem tra game da ket thuc chua, xu li thang thua
void Game::gameLogic()
{
	//Kiem tra xem ball da cham tuong tren hoac duoi chua, neu co thi dao nguoc HeadingY()
	if ((ball.Y() < SCREEN_TOP) || (ball.Y() > SCREEN_BOTTOM - 2))
	{
		ball.SetHeadingY(-ball.HeadingY());
	}

	//Kiem tra su va cham cua ball va pad
	if ((ball.Y() >= PlayersPad.HeadY()) && (ball.Y() <= PlayersPad.HeadY() + PlayersPad.Length()) && (ball.X() <= PlayersPad.HeadX() + 1))
	{
		ball.SetHeadingX(-ball.HeadingX());
		playersScore += 10;
		count /= 0.9;
	}

	if ((ball.Y() >= computersPad.HeadY()) && (ball.Y() <= computersPad.HeadY() + PlayersPad.Length()) && (ball.X() >= computersPad.HeadX() - 1))
	{
		ball.SetHeadingX(-ball.HeadingX());
		computersScore += 10;
	}

	/* if cheat enabled,let player track ball's movement */
	if (isPlayer2 < 0)
	{
		/* let computer track ball's movement */
		if (ball.X() > GAME_BORDER_RIGHT / 2) {
			if (ball.Y() < computersPad.HeadY() + computersPad.Length() / 2) {
				computersPad.MoveUp();
			}
			else computersPad.MoveDown();
		}
		else {
			// computer go to center
			if ((GAME_BORDER_BOTTOM - GAME_BORDER_TOP) / 2 < computersPad.HeadY() + computersPad.Length() / 2) {
				computersPad.MoveUp();
			}
			else computersPad.MoveDown();
		}

		if ((ball.X() >= GAME_BORDER_RIGHT - 1))
		{
			ball.SetHeadingX(-ball.HeadingX());
			computersScore += 10;
		}
	}

	//Kiem tra neu ball khong cham pad
	if (ball.X() <= GAME_BORDER_LEFT + 1)
	{
		displayYouMissed();
		ball.Erase();
		ball.SetPos({ 15,15 });
	}
	if (ball.X() >= GAME_BORDER_RIGHT - 1)
	{
		displayYouMissed();
		ball.Erase();
		ball.SetPos({ 15,15 });
	}
}

bool Game::gameLogicEatingGame()
{
	//Kiem tra xem ball da cham tuong tren hoac duoi chua, neu co thi dao nguoc HeadingY()
	if (ball.Y() < SCREEN_TOP && ball.HeadingY() < 0)
	{
		ball.SetHeadingY(-ball.HeadingY());
	}
	if (ball.Y() > SCREEN_BOTTOM - 2 && ball.HeadingY() > 0)
	{
		ball.SetHeadingY(-ball.HeadingY());
	}

	//Kiem tra su va cham cua ball va pad
	if ((ball.Y() >= PlayersPad.HeadY()) && (ball.Y() <= PlayersPad.HeadY() + PlayersPad.Length()) && (ball.X() <= PlayersPad.HeadX() + 1))
	{
		ball.SetHeadingX(-ball.HeadingX());
		//playersScore += 10;
		count += 1;
	}

	/* if cheat enabled,let player track ball's movement */
	//if (isPlayer2 < 0)
	//{
	//	/* let computer track ball's movement */
	//	if (ball.X() > SCREEN_RIGHT - 18) computersPad.y = ball.Y();
	//	if ((ball.X() > SCREEN_RIGHT))
	//	{
	//		ball.SetHeadingX(-ball.HeadingX());
	//		computersScore += 10;
	//	}
	//}

	if (isPlayer2 < 0)
	{
		/* let computer track ball's movement */
		if (ball.X() < GAME_BORDER_RIGHT / 2) {
			if (ball.Y() < PlayersPad.HeadY() + PlayersPad.Length() / 2) {
				PlayersPad.MoveUp();
				if ((ball.Y() >= PlayersPad.HeadY()) && (ball.Y() <= PlayersPad.HeadY() + PlayersPad.Length()) && ball.X() == PlayersPad.HeadX() + 1 && ball.Y() > GAME_BORDER_TOP + 2) {
					ball.SetPos(ball.X(), ball.Y() - 1);
				}
			}
			else {
				PlayersPad.MoveDown();
				if ((ball.Y() >= PlayersPad.HeadY()) && (ball.Y() <= PlayersPad.HeadY() + PlayersPad.Length()) && ball.X() == PlayersPad.HeadX() + 1 && ball.Y() > GAME_BORDER_BOTTOM - 2) {
					ball.SetPos(ball.X(), ball.Y() + 1);
				}
			} 
		}
		else {
			// computer go to center
			if ((GAME_BORDER_BOTTOM - GAME_BORDER_TOP) / 2 < PlayersPad.HeadY() + PlayersPad.Length() / 2) {
				PlayersPad.MoveUp();
			}
			else PlayersPad.MoveDown();
		}
	}

	//Kiem tra neu ball khong cham pad
	if (ball.X() <= GAME_BORDER_LEFT + 1)
	{
		displayYouMissed();
		ball.Erase();
		ball.SetPos({ 45,15 });
		computersScore += 10;

		return false;
	}

	if (ball.X() >= GAME_BORDER_RIGHT - 1)
	{
		ball.SetHeadingX(-ball.HeadingX());
	}

	return true;
}

void Game::MoveBall()
{
	Point newPos;
	newPos.x = ball.X() + ball.HeadingX();
	newPos.y = ball.Y() + ball.HeadingY();

	ball.Erase();
	ball.SetPos(newPos);
}

// INPUT:
// OUTPUT:
// Khoi tao gia tri mac dinh cho cac bien trong tro choi
void  Game::initGame()
{

	playersScore = 0;
	computersScore = 0;
	ball.SetPos({ 15,5 });
	ball.SetHeadingX(1);
	ball.SetHeadingY(1);
	count = 1;

	PlayersPad.SetPoint({ 5, 12 });
	computersPad.SetPoint({ 73, 12 });
	
	//displayCheatEnabled();

	setTextColor(15);
	clrscr();
	txtLine(GAME_BORDER_LEFT, 0, GAME_BORDER_RIGHT, 0, GREY);
	txtLine(GAME_BORDER_LEFT, 22, GAME_BORDER_RIGHT, 22, GREY);
	txtLine(GAME_BORDER_LEFT, 23, GAME_BORDER_RIGHT, 23, GREY);

	// Vertical lile 
	txtLine(GAME_BORDER_LEFT, 0, GAME_BORDER_LEFT, 23, GREY);
	txtLine(GAME_BORDER_RIGHT, 0, GAME_BORDER_RIGHT, 23, GREY);

	//if (isPlayer2 > 0)
	//{
	//	setTextColor(79); gotoXY(62, 23); cout << " 2 Player "; setTextColor(15);
	//}
	//else
	//{
	//	setTextColor(79); gotoXY(62, 23);  cout << " 1 Player "; setTextColor(15);
	//}

}

//
// INPUT:
// OUTPUT:
// Xu li thua
void Game::displayYouMissed()
{
	clrbox(10, 8, 70, 16, 79);
	char a[] = "You missed";
	box(10, 8, 70, 16, a);

	gotoXY(18, 10); cout << "";
	gotoXY(18, 11); cout << "The ball has missed the paddle";
	gotoXY(18, 12); cout << "Press SPACE to PLAY AGAIN";
	gotoXY(18, 13); cout << "Press ESC key to EXIT";
	gotoXY(18, 14); cout << "";
	
	SaveRanking(_name);

	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE)) {
			clrbox(10, 8, 71, 21, 0);
			break;
		};

		if (GetAsyncKeyState(VK_ESCAPE)) {
			clrbox(10, 8, 70, 16, 79);
			clrscr();
			exit(0);
			break;
		};
	}
}

void Game::displayYouWin()
{
	clrbox(10, 8, 70, 16, 79);
	char a[] = "CONRATULATION YOU WIN";
	box(10, 8, 70, 16, a);

	gotoXY(18, 10); cout << " ";
	gotoXY(18, 11); cout << "NICE! You have eat all the food";
	gotoXY(18, 12); cout << "Press SPACE to PLAY AGAIN";
	gotoXY(18, 13); cout << "Press ESC key to EXIT";
	gotoXY(18, 14); cout << "";

	SaveRanking(_name);

	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE)) {
			clrbox(10, 8, 71, 21, 0);
			break;
		};

		if (GetAsyncKeyState(VK_ESCAPE)) {
			clrbox(10, 8, 70, 16, 79);
			clrscr();
			exit(0);
			break;
		};
	}
}

void Game::SaveRanking(string username)
{
	// Update listRank
	SaveGame localhost;
	vector<Top> listRank;

	localhost.LoadRanking(listRank);

	Top curTop;
	curTop.name = username;
	curTop.score = playersScore;

	if (listRank.empty()) {
		listRank.push_back(curTop);
	}
	else {
		int i = 0;
		for (; i < listRank.size(); i++) {
			if (curTop.score > listRank[i].score) break;
		}

		listRank.insert(listRank.begin() + i, curTop);
	}

	localhost.SaveRanking(listRank);
}

void Game::SaveGameState(string name)
{
	// Update 
	SaveGame localhost;

	localhost.SaveGameState(name, ball, PlayersPad, _obstacles.Obstacles(), playersScore);


}

void Game::PauseGame()
{
	clrbox(10, 8, 70, 16, 79);
	char a[] = "Game Paused";
	box(10, 8, 70, 16, a);

	gotoXY(18, 10); cout << "";
	gotoXY(18, 12); cout << "Press SPACE to CONTINUE";
	gotoXY(18, 13); cout << "Press ESC key to EXIT";
	gotoXY(18, 14); cout << "";

	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE)) {
			clrbox(10, 8, 71, 21, 0);
			break;
		};

		if (GetAsyncKeyState(VK_ESCAPE)) {
			clrbox(10, 8, 70, 16, 79);
			clrscr();
			setTextColor(WHITE);
			exit(0);
			break;
		};
	}
}

void Game::DisplaySavedGame()
{
	clrbox(10, 8, 70, 16, 79);
	char a[] = "Game Saved";
	box(10, 8, 70, 16, a);

	gotoXY(18, 10); cout << "";
	gotoXY(18, 12); cout << "Press SPACE to CONTINUE";
	gotoXY(18, 13); cout << "Press ESC key to EXIT";
	gotoXY(18, 14); cout << "";

	SaveGameState("curent_state");

	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE)) {
			clrbox(10, 8, 71, 21, 0);
			break;
		};

		if (GetAsyncKeyState(VK_ESCAPE)) {
			clrbox(10, 8, 70, 16, 79);
			clrscr();
			setTextColor(WHITE);
			exit(0);
			break;
		};
	}
}

void Game::DisplayLoadedGame()
{
	clrbox(10, 8, 70, 16, 79);
	char a[] = "Game Loaded";
	box(10, 8, 70, 16, a);

	gotoXY(18, 10); cout << "";
	gotoXY(18, 12); cout << "Press SPACE to CONTINUE";
	gotoXY(18, 13); cout << "Press ESC key to EXIT";
	gotoXY(18, 14); cout << "";

	SaveGame localhost;
	localhost.LoadGameState(_name, ball, PlayersPad, Obstacles().Obstacles(), playersScore);

	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE)) {
			clrbox(10, 8, 71, 21, 0);
			break;
		};

		if (GetAsyncKeyState(VK_ESCAPE)) {
			clrbox(10, 8, 70, 16, 79);
			clrscr();
			setTextColor(WHITE);
			exit(0);
			break;
		};
	}
}

void Game::DisplayEnterName()
{
	clrbox(10, 8, 70, 16, 79);
	char a[] = "Enter Player Info";
	box(10, 8, 70, 16, a);

	gotoXY(18, 10); cout << "";
	gotoXY(18, 12); cout << "Press Enter to CONTINUE";
	gotoXY(18, 13); cout << "";
	gotoXY(18, 14); cout << "";
	gotoXY(18, 11); cout << "Enter your name > ";
	getline(cin, _name);

	clrbox(10, 8, 71, 17, 0);
}

// INPUT: 
// OUTPUT: 
// Xu li cac phim nhap vao tuong ung voi cac chuc nang
int Game::Keypressed()
{
	if (GetAsyncKeyState(VK_UP)) {
		computersPad.MoveUp();
	};

	if (GetAsyncKeyState(VK_DOWN)) {
		computersPad.MoveDown();
	};
	//

	if (GetAsyncKeyState(VK_W)) {
		PlayersPad.MoveUp();
		if ((ball.Y() >= PlayersPad.HeadY()) && (ball.Y() <= PlayersPad.HeadY() + PlayersPad.Length()) && ball.X() == PlayersPad.HeadX() + 1 && ball.Y() > GAME_BORDER_TOP + 2) {
			ball.SetPos(ball.X(), ball.Y() - 1);
		}
	};

	if (GetAsyncKeyState(VK_S)) {
		PlayersPad.MoveDown();
		if ((ball.Y() >= PlayersPad.HeadY()) && (ball.Y() <= PlayersPad.HeadY() + PlayersPad.Length()) && ball.X() == PlayersPad.HeadX() + 1 && ball.Y() > GAME_BORDER_BOTTOM - 2) {
			ball.SetPos(ball.X(), ball.Y() + 1);
		}
	};

	if (GetAsyncKeyState(VK_ESCAPE)) {
		clrscr();
		exit(0);
	};

	if (GetAsyncKeyState(VK_N)) {
		initGame();
		return 1;
	};

	if (GetAsyncKeyState(VK_P)) {
		PauseGame();
	};

	if (GetAsyncKeyState(VK_L)) {
		SaveGameState(_name);
		DisplaySavedGame();
	};

	if (GetAsyncKeyState(VK_TAB)) {
		isPlayer2 = -isPlayer2;
		/*if (isPlayer2 > 0)
		{
			setTextColor(79); gotoXY(62, 23); printf("2 Player "); setTextColor(15);
		}
		else
		{
			setTextColor(79); gotoXY(62, 23); printf("1 Player  "); setTextColor(15);
		}*/
	};

	return 0;
}

//
// INPUT:
// OUTPUT:
// Xoa console
void Game::clrscr()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
	
}

// INPUT:
// OUTPUT:
// tra ra gia tri bien PlayersScore: diem cua nguoi choi
int& Game::getPlayersScore()
{
	return playersScore;
}

// INPUT:
// OUTPUT:
// tra ra gia tri bien ComputerScore: diem cua may
int Game::getComputersScore()
{
	return computersScore;
}

Ball& Game::GetBall()
{
	return ball;
	// TODO: insert return statement here
}

Pad& Game::GetPlayerPad()
{
	return PlayersPad;
}

Pad& Game::GetComputerPad()
{
	return computersPad;
}

// INPUT:
// OUTPUT:
// tra ra so lan va cham cua ball va pad
int Game::getCount()
{
	return count;
}

// INPUT:
// OUTPUT:
// gan gia tri cho bien isPlayer2: chuyen che do player hoac computer
void Game::setIsPlayer2(int data)
{
	isPlayer2 = data;
}

// INPUT:
// OUTPUT:
// tra ra gia tri cho bien isPlayer2: chuyen che do player hoac computer
int Game::getIsPlayer2()
{
	return isPlayer2;
}

ObjectManager& Game::Obstacles()
{
	return _obstacles;
}

// INPUT:
// OUTPUT:
// Tao ra mot hop van ban
void Game::box(int x, int y, int sx, int sy,char text_[])
{
	unsigned i, j, m;
	{

		m = (sx - x);                       //differential
		j = m / 8;                          //adjust
		j = j - 1;                          //more adjustment
		gotoXY(x, y); cout << char(219);       //Top left corner of box
		gotoXY(sx, y); cout << char(219);        //Top right corner of box
		gotoXY(x, sy); cout << char(219);        //Bottom left corner of box
		gotoXY(sx, sy); cout << char(219);     //Bottom right corner of box

		for (i = x + 1; i < sx; i++)
		{
			gotoXY(i, y); cout << char(219);       // Top horizontol line
			gotoXY(i, sy); cout << char(219);     // Bottom Horizontal line
		}

		for (i = y + 1; i < sy; i++)
		{
			gotoXY(x, i); cout << char(219);       //Left Vertical line
			gotoXY(sx, i); cout << char(219);       //Right Vertical Line
		}

		gotoXY(x + j, y); cout << text_;    //put Title
		gotoXY(1, 24);
	}
}

//
// INPUT:
// OUTPUT:
// Xoa hop van ban
void Game::clrbox(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char bkcol)
{
	int x, y;
	setTextColor(bkcol);                       //Set to color bkcol

	for (y = y1; y < y2; y++)                    //Fill Y Region Loop
	{
		for (x = x1; x < x2; x++)               //Fill X region Loop
		{
			gotoXY(x, y); cout << " ";          //Draw Solid space
		}
	}
}
