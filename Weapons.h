#include "DynamicObject.h"
#include "includes.h"
#ifndef WEAPONS_H
#define WEAPONS_H
class Weapons:public DynamicObject
{
	public:
		Weapons(Type,float,float);
		~Weapons();
	  	void move(int);
	  	virtual void render();
};
#endif