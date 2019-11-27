#include "Object.h"
#include <vector>

#ifndef DynamicObject_H
#define DynamicObject_H

class DynamicObject:public Object
{
	protected:
		int ttl;

	public:
		bool collisionY=false;
		float bouncer_dx;
		float bouncer_dy;
		DynamicObject(Type);
		virtual~DynamicObject();
		virtual void render();
		virtual void move()=0;
		virtual bool collisionWithObstacle(float,float,int,int);
		int getTtl();
  		void decreaseTtl();
};
#endif