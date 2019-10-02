#include "Object.h"
#ifndef DynamicObject_H
#define DynamicObject_H

class DynamicObject:public Object
{
	protected:
	float bouncer_x;
	float bouncer_y; 
	public:
		DynamicObject(int,Type);
		virtual~DynamicObject();
		virtual void tick()=0;
		virtual void render()=0;
		virtual void die()=0;
		virtual void move(int,int)=0; 

		void setBouncer_x(float);
		void setBouncer_y(float);
		float getBouncer_x();
		float getBouncer_y();
};
#endif