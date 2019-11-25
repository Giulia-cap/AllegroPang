#include "DynamicObject.h"
#ifndef Ball_H
#define Ball_H

class Ball:public DynamicObject
{
	public:
		Ball(Type,int,float,float,float,float);
		~Ball();
		void move(int);
};
#endif