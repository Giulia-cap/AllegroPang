#include "DynamicObject.h"
#ifndef Balls_H
#define Balls_H

class Balls:public DynamicObject
{
	private:
		float bouncer_dx = -4.0;
		float bouncer_dy = 4.0;
	public:
		Balls(int,Type,int);
		~Balls();
		void move(int,int);
		void loadImage();
		void tick();
		void render();
		void die();
};
#endif