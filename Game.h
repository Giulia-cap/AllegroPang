#include <stdio.h>
#include <allegro5/allegro.h>
#include <iostream>
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
};
#endif