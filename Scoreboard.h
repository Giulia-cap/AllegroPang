#include"includes.h"
#include<list>
#include<vector>
#include <string>
#include <sstream>
#include<fstream>
#ifndef Scoreboard_H
#define Scoreboard_H

class Scoreboard : public list<int>
{
public:
		Scoreboard();
		void addScore(int);
		void showScoreboard();
		vector<string> readFromFile();

};
#endif