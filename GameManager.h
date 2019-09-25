#include <stdio.h>
#include <iostream>
#include <allegro5/allegro.h>
#include <list>
#include "Player.h"
using namespace std;
#ifndef GameManager_H
#define GameManager_H

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

class GameManager
{
	private:
		ALLEGRO_DISPLAY *display;
		//Player player;
		list<int> object;
   	public:
   		GameManager();
   		~GameManager();
   		void init();
   		void random();
   		void tick();
   		void render();
   		void gameOver();
   		void win();
};
#endif