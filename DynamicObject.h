#include "Object.h"
#include <vector>

#ifndef DynamicObject_H
#define DynamicObject_H

class DynamicObject:public Object
{
	protected:
		int ttl;
		vector<ALLEGRO_BITMAP *>  explosionImage;

	public:
		bool collisionX=false;
		bool collisionY=false;

		float bouncer_dx;
		float bouncer_dy;
		DynamicObject(Type);
		virtual~DynamicObject();
		virtual void render();
		virtual void move()=0;
		virtual void changeMovement();

		//virtual void changeMovement();
		bool collisionWithObstacle(float,float,int,int);
		int getTtl();
  		void decreaseTtl();
  		void explodeAnimation();
};
#endif