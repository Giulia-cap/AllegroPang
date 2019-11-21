#include "Object.h"
#ifndef DynamicObject_H
#define DynamicObject_H

class DynamicObject:public Object
{
	private:
		int ttl;
	public:
		float bouncer_dx;
		float bouncer_dy;
		DynamicObject(Type);
		virtual~DynamicObject();
		virtual void render()=0;
		virtual void move(int)=0;
		int getTtl();
  		void decreaseTtl();
};
#endif