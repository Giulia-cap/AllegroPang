#include <stdio.h>
#include <allegro5/allegro.h>
#include "Player.h"
#include "Ball.h"
#include "Bullet.h"
#include "Object.h"
#include <iostream>
#include <list>
#include "State.h"
#include "Bonus.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
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
		list<Bonus*> bonus;
		int bulletDelay;
		int firerate;
		int level=1;
		ALLEGRO_FONT * pangFont;
	public:
		GameState(ALLEGRO_DISPLAY * &,ALLEGRO_EVENT_QUEUE * &,ALLEGRO_TIMER * &, int,int);
		~GameState();
		
		void generateBalls();
		void gameOver();
		bool checkCollision(list<DynamicObject*>::iterator );
		bool checkLevelOver();
		void reset();
		void findPower(int);
		void drawLife();
		

		void init();
		void tick();
		void render();

		bool finish;

		int getLevel(){return level;}
		void setLevel(int l){level=l;}
};
#endif