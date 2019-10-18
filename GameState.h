#include <stdio.h>
#include <allegro5/allegro.h>
#include "Player.h"
#include "Ball.h"
#include "Bullet.h"
#include "Object.h"
#include <iostream>
#include <list>
#include "State.h"
#ifndef GameState_H
#define GameState_H

enum MYKEYS {
   KEY_LEFT, KEY_RIGHT , SPACE_BAR 
};

class GameState:public State
{
	private:
		Player *player;
		list<DynamicObject*> object;
		int bulletDelay=10.0f;
		int firerate=10.0f;
	public:
		GameState(ALLEGRO_DISPLAY * &,ALLEGRO_EVENT_QUEUE * &, int,int);
		~GameState();
		
		void generateBalls();
		void gameOver();
		bool checkCollision(list<DynamicObject*>::iterator );
		bool checkLevelOver();

		void init();
		void tick();
		void render();

		bool finish=false;
};
#endif