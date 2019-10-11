#include <stdio.h>
#include <allegro5/allegro.h>
#include "Player.h"
#include "Ball.h"
#include "Bullet.h"
#include "Object.h"
#include <iostream>
#include <vector>
#ifndef Game_H
#define Game_H

enum MYKEYS {
   KEY_LEFT, KEY_RIGHT , SPACE_BAR 
};

class Game
{
	private:
	int SCREEN_W=640; 
	int SCREEN_H=480;
	Player *player;
	vector<DynamicObject*> object;
	int bulletDelay=10.0f;
	int firerate=10.0f;

	public:
		Game(int,int);
		~Game();
		void init();
		void generateBalls();
		void gameOver();
		bool checkCollision(vector<DynamicObject*>::iterator );
		void tick();
		void render();
		bool checkLevelOver();



};
#endif