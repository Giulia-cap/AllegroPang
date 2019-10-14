#include "DynamicObject.h"
#include <vector>
#ifndef Player_H
#define Player_H

class Player:public DynamicObject
{
	/*private:
		vector<ALLEGRO_BITMAP *> imagedx;
		vector<ALLEGRO_BITMAP *> imagesx;
		int movDx=0;
		int moSx=0;
		bool dx=false,sx=false;*/
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