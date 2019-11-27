#include "DynamicObject.h"
#include "includes.h"
#ifndef WEAPONS_H
#define WEAPONS_H
class Weapons:public DynamicObject
{
	private:
		string typeWeapons;
	public:
		bool stop=false;
		Weapons(Type,float,float,string);
		~Weapons();
	  	void move();
	  	virtual void render();
	  	virtual bool collisionWithObstacle(float, float, int, int);
};
#endif