#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "structPad.h"
#include "structBall.h"
#include "ObjectManager.h"
#include <fstream>

using namespace std;
struct Top {
    string name;
    int score;
};

class SaveGame
{
public:
    const char SEPERATOR = ',';
public:

    void SaveGameState(string& name, Ball&, Pad&, vector<shared_ptr<Obstacle>>& obstacles, int& score);
    void LoadGameState(string& name, Ball&, Pad&, vector<shared_ptr<Obstacle>>& obstacles, int& score);
    vector<string> Tokenlizer(string line, char SEPERATOR);

    void LoadRanking(vector<Top>& ranking);
    
    void SaveRanking(vector<Top>& ranking);
};


