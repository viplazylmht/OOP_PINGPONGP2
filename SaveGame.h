#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "structPad.h"
#include "structBall.h"
#include "Obstacle.h"
#include <fstream>

using namespace std;
struct Top {
    string name;
    int score;
};

class SaveGame
{
public:
    static const char SEPERATOR = ',';
public:
    SaveGame();

    static void SaveGameState(string& name, Ball&, Pad&, vector<Obstacle>&, int& score);
    static void LoadGameState(string& name, Ball&, Pad&, vector<Obstacle>&, int& score);
    static vector<string> Tokenlizer(string line, char SEPERATOR);

    static void LoadRanking(vector<Top>& ranking);
    
    static void SaveRanking(vector<Top>& ranking);
    ~SaveGame();
};

SaveGame::SaveGame(/* args */)
{
}

SaveGame::~SaveGame()
{
}

