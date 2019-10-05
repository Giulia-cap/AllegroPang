#include "DynamicObject.h"
#ifndef Balls_H
#define Balls_H

class Balls:public DynamicObject
{
	private:
		float bouncer_dx;
		float bouncer_dy;
	public:
		Balls(int,Type,int,float,float,float,float);
		~Balls();
		void move(int,int);
		void loadImage();
		void tick();
		void render();
		void die();
};
#endif