#include "includes.h"
#include "Object.h"

#ifndef Obstacle_H
#define Obstacle_H

class Obstacle:public Object
{
	public:
		int BOUNCER_SIZEX=128;
		bool collisionX=false;
		bool collisionY=false;
		Obstacle(Type t,float pox,float poy):Object(t)
		{
			bouncer_x=pox;
			bouncer_y=poy;
			BOUNCER_SIZE=32;
			image=al_load_bitmap("./resources/obstacle.png");
		}
		~Obstacle(){}
		void render()
		{
			al_draw_bitmap(image,bouncer_x, bouncer_y, 0);
		}
		bool collision(float x, float y, int size)
		{
			 if ((bouncer_x > x + size ) || // is b1 on the right side of b2?
		        (bouncer_y > y + size ) || // is b1 under b2?
		        (x > bouncer_x + BOUNCER_SIZEX ) || // is b2 on the right side of b1?
		        (y > bouncer_y + BOUNCER_SIZE ))   // is b2 under b1?
		        return false;

		    if(bouncer_y == y+size && bouncer_x == x+size){ collisionY=true;}
		    if( bouncer_x == x+size){ collisionX=true;}

			if(bouncer_y+BOUNCER_SIZE == y+size) collisionY=true;
			if(bouncer_x+BOUNCER_SIZEX == x+size) collisionX=true; 

			if(bouncer_y+BOUNCER_SIZE == y) collisionY=true;
			if(bouncer_x+BOUNCER_SIZEX == x) collisionX=true; 

		    /*
		    if( (bouncer_y == y+size && bouncer_x == x+size)//V
		    	||(bouncer_x == x+size && bouncer_x+BOUNCER_SIZEX == x)
		    	||(bouncer_x+BOUNCER_SIZEX == x+size && bouncer_y+BOUNCER_SIZE == y+size)
		    	||(bouncer_x+BOUNCER_SIZEX == x && bouncer_y+BOUNCER_SIZE == y) )
		    { collisionY=true; collisionX=true;}*/ //------>ANGOLI

			return true;
		}
};
#endif 