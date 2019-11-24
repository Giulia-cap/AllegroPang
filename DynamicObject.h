#include "Object.h"
#ifndef DynamicObject_H
#define DynamicObject_H

class DynamicObject:public Object
{
	private:
		int ttl;
	public:
		bool collisionX=false;
		bool collisionY=false;

		float bouncer_dx;
		float bouncer_dy;
		DynamicObject(Type);
		virtual~DynamicObject();
		virtual void render()=0;
		virtual void move(int)=0;
		virtual void changeMovement();
		bool collisionWithObstacle(float,float,int,int);
		int getTtl();
  		void decreaseTtl();
};
#endif