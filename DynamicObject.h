#include "Object.h"
#ifndef DynamicObject_H
#define DynamicObject_H

class DynamicObject:public Object
{
	public:
		DynamicObject(int,Type);
		virtual~DynamicObject();
		virtual void tick()=0;
		virtual void render()=0;
		virtual void die()=0;
		virtual void move(int,int)=0;
};
#endif