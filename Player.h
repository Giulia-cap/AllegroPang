#include "DynamicObject.h"
#ifndef Player_H
#define Player_H

class Player:public DynamicObject
{

	public:
		Player(int,Type);
		~Player();
		void move(int,int);
		void loadImage();
		void tick();
		void render();
		void die();
};
#endif