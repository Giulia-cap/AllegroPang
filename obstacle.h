#include "includes.h"
#include "Object.h"

#ifndef Obstacle_H
#define Obstacle_H

class Obstacle:public Object
{
	public:
		Obstacle(Type t,float pox,float poy):Object(t)
		{
			bouncer_x=pox;
			bouncer_y=poy;
			image=al_load_bitmap("./resources/obstacle.png");
		}
		~Obstacle(){}
		void render()
		{
			al_draw_bitmap(image,bouncer_x, bouncer_y, 0);
		}

};
#endif 