#include <stdio.h>
#include <allegro5/allegro.h>
#include <iostream>
#include <list>
#include "Scoreboard.h"
#ifndef Game_H
#define Game_H

class Game
{
	private:
	int SCREEN_W=640; 
	int SCREEN_H=480;
	Scoreboard scores;
	public:
		Game(int,int);
		~Game();
		void init();
		void tick();
		bool esci=false;
		void setEsc(bool e){esci=e;}

};
#endif