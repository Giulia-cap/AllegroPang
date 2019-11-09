#include "DynamicObject.h"
#ifndef Ball_H
#define Ball_H

class Ball:public DynamicObject
{
	public:
		Ball(int,Type,int,float,float,float,float);
		~Ball();
		void move(int);
		void render();
		void die();


};
#endif