#include"includes.h"
#include <list>
#ifndef Game_H
#define Game_H

class Game
{
	private:
	int SCREEN_W=640; 
	int SCREEN_H=480;

	public:
		Game(int,int);
		~Game();
		void init();
		void tick();
		//void setEsc(bool e){esci=e;}
};
#endif