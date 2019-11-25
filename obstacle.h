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
			BOUNCER_SIZE=32;  //32
			BOUNCER_SIZEX=128; //128
			image=al_load_bitmap("./resources/obstacle.png");
		}
		~Obstacle(){}
		void render()
		{
			al_draw_bitmap(image,bouncer_x, bouncer_y, 0);
			//al_draw_rectangle(bouncer_x,bouncer_y,bouncer_x+BOUNCER_SIZEX,bouncer_y+BOUNCER_SIZE,al_map_rgb(200, 0, 0),0);
		}
};
#endif 