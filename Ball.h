#include "DynamicObject.h"
#ifndef Ball_H
#define Ball_H

class Ball:public DynamicObject
{
	private:
		float bouncer_dx;
		float bouncer_dy;
	public:
		Ball(int,Type,int,float,float,float,float);
		~Ball();
		void move(int,int);
		void loadImage();
		void tick();
		void render();
		void die();
};
#endif