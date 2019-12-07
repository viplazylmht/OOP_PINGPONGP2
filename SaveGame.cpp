#include "SaveGame.h"

void SaveGame::SaveGameState(string& name, Ball& ball, Pad& pad, vector<shared_ptr<Obstacle>>& obstacles, int& score) {
    string filename = "data/gamesave.txt";
    // Check if wrong path cause of Open direct execute program in Output folder instead of Visual Studio
	ofstream testf(filename);
	if (testf.fail()) {
		// redirect to prev folder that contains data
		filename = "..\\" + filename;
	}
	else {
		testf.close();
	}

    ofstream fout(filename);

    if (fout.fail()) return;

    //
    fout << "# file name" << endl << name << endl;

    fout << "# Ball - x, y, vectorX, vectorY" << endl
         << ball.X() << SEPERATOR << ball.Y() << SEPERATOR
         << ball.HeadingX() << SEPERATOR << ball.HeadingY() << endl;

    fout << "# Pad - x, y, Length, isVisible" << endl
         << pad.HeadX() << SEPERATOR << pad.HeadY() << SEPERATOR << pad.Length()
		<< SEPERATOR << pad.isVisible() << endl;
    
    fout << "# Score" << endl << score << endl;

    fout << "# Obstacles - vector<text, color, x, y, isVisible>" << endl;

    for (auto item : obstacles) {

        fout << item->GetText() << SEPERATOR << item->GetColor() << SEPERATOR
             << item->GetPoint().x << SEPERATOR << item->GetPoint().y << SEPERATOR
             << (int)item->IsVisible() << endl;
    }

    fout.close();
}

void SaveGame::LoadGameState(string& name, Ball& ball, Pad& pad, vector<shared_ptr<Obstacle>>& obstacles, int& score) {
    string filename = "data/gamesave.txt";
    // Check if wrong path cause of Open direct execute program in Output folder instead of Visual Studio
	ifstream testf(filename, ios::in);
	if (testf.fail()) {
		// redirect to prev folder that contains data
		filename = "..\\" + filename;
	}
	else {
		testf.close();
	}

    ifstream fin(filename);

    if (fin.fail()) return;
    
    string line;
    int count = 0;
    obstacles.clear();

    while (getline(fin, line)) {
        if (line.length() <= 0 || line[0] == '#') continue;

        if (count == 0) {
            // name
            name = line;
        }
        
        if (count == 1) {
            // Ball
            vector<string> tokens = Tokenlizer(line, SEPERATOR);
            int x = (tokens[0].length() > 0) ? stoi(tokens[0]) : 1;
            int y = (tokens[1].length() > 0) ? stoi(tokens[1]) : 1;
            int headingX = (tokens[2].length() > 0) ? stoi(tokens[2]) : 1;
            int headingY = (tokens[3].length() > 0) ? stoi(tokens[3]) : 1;
        
            ball.SetPos(x, y);
            ball.SetHeadingX(headingX);
            ball.SetHeadingY(headingY);

        }

        if (count == 2) {
            // Pad
            vector<string> tokens = Tokenlizer(line, SEPERATOR);
            int x = (tokens[0].length() > 0) ? stoi(tokens[0]) : 1;
            int y = (tokens[1].length() > 0) ? stoi(tokens[1]) : 1;
            int length = (tokens[2].length() > 0) ? stoi(tokens[2]) : 1;
            int isVisible = (tokens[3].length() > 0) ? stoi(tokens[3]) : 1;
        
			pad.SetPoint(x, y);
			pad.SetLength(length);
			pad.SetVisible(isVisible);
        }

        if (count == 3) {
            // score
            vector<string> tokens = Tokenlizer(line, SEPERATOR);
            int x = (tokens[0].length() > 0) ? stoi(tokens[0]) : 0;

            score = x;
        }

        if (count > 3) {
            // Obstacles[i]

            vector<string> tokens = Tokenlizer(line, SEPERATOR);
            char text = tokens[0].length() > 0 ? tokens[0][0] : ' ';

            int color = (tokens[1].length() > 0) ? stoi(tokens[1]) : RED;
            int x = (tokens[2].length() > 0) ? stoi(tokens[2]) : 1;
            int y = (tokens[3].length() > 0) ? stoi(tokens[3]) : 1;
            int isVisible = (tokens[4].length() > 0) ? stoi(tokens[4]) : false;

            if (text == BONUS_X2_TEXT || text == MINUS_TEXT) {    
                obstacles.push_back(make_shared<Bonus>(Bonus(text, {x, y}, color, isVisible)));
            }
            
            if (text == FOOD_TEXT) {
                obstacles.push_back(make_shared<Food>(Food(text, { x, y }, color, isVisible)));
            }

            if (text == WALL_TEXT) {
                obstacles.push_back(make_shared<Wall>(Wall(text, { x, y }, color, isVisible)));
            }
        }

        count++;
    }

    fin.close();
};


void SaveGame::LoadRanking(vector<Top>& ranking) {
    string filename = "data/ranking.txt";
    // Check if wrong path cause of Open direct execute program in Output folder instead of Visual Studio
	ifstream testf(filename, ios::in);
	if (testf.fail()) {
		// redirect to prev folder that contains data
		filename = "..\\" + filename;
	}
	else {
		testf.close();
	}

    ifstream fin(filename);

    if (fin.fail()) return;
    
    string line;
    ranking.clear();

    while (getline(fin, line)) {
        if (line.length() <= 0 || line[0] == '#') continue;
        vector<string> tokens = Tokenlizer(line, SEPERATOR);

        if (tokens.size() < 2) continue;
        int score = (tokens[1].length() > 0) ? stoi(tokens[1]) : 0;

        Top tmp;
        tmp.name = tokens[0];
        tmp.score = score;
        ranking.push_back(tmp);    
    }

    fin.close();
}

void SaveGame::SaveRanking(vector<Top>& ranking) {
    string filename = "data/ranking.txt";
    // Check if wrong path cause of Open direct execute program in Output folder instead of Visual Studio
	ofstream testf(filename);
	if (testf.fail()) {
		// redirect to prev folder that contains data
		filename = "..\\" + filename;
	}
	else {
		testf.close();
	}

    ofstream fout(filename);

    if (fout.fail()) return;

    //
    fout << "# Top 100 ranking" << endl;

    int size = (ranking.size() < 100) ? ranking.size() : 100;

    for (int i = 0; i < size; i++) {

        fout << ranking[i].name << SEPERATOR << ranking[i].score << endl;
        if ((i+1) % 10 == 0) fout << "# TOP " << (i+1) << endl;
    }

    fout << "# Top 100 end Here" << endl;
    
    fout.close();

}


vector<string> SaveGame::Tokenlizer(string line, char SEPERATOR)
{
	vector<string> out;
	if (line.length() <= 0) return out;

	int start = 0;
	int pos;

	string temp = "";
	pos = line.find_first_of(SEPERATOR, start);

	while (pos >= 0) {
		temp = line.substr(+start, pos - start);
		out.push_back(temp);
		start = pos + 1;
		pos = line.find_first_of(SEPERATOR, start);
	}

	if (start < line.length()) out.push_back(line.substr(start, line.length()));

	return out;
}
