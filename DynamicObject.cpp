#include "DynamicObject.h"
using namespace std;
  
DynamicObject::DynamicObject(Type t):Object(t){
	ttl=250;

}
DynamicObject::~DynamicObject(){}

int DynamicObject::getTtl(){
	return ttl;
}
void DynamicObject::decreaseTtl()
{
	if(ttl>0)
		ttl-=1;
}

bool DynamicObject::collisionWithObstacle(float x, float y, int sizex, int sizey)
{
	if(!collisionY)
	{
		if(!collision(x,y,sizex,sizey))return false;
		if (bouncer_x+BOUNCER_SIZE<=x && bouncer_y <= y+sizey)
		{
			collisionY=true;
			bouncer_dy=-(bouncer_dy);
			bouncer_dx=-(bouncer_dx);
			return true;
		}
		if (bouncer_x>=x+sizex && bouncer_y<=y+sizey) 
		{ 
			collisionY=true;
			bouncer_dy=-(bouncer_dy);
			bouncer_dx=-(bouncer_dx);
		  	return true;
		}
		else
		{
			if(bouncer_y <= y)
			{
				bouncer_dy=-(bouncer_dy); 
				return true;
			}
		    else if(bouncer_y >= y)
		    {
		    	bouncer_dy=-(bouncer_dy); 
		    	collisionY=true;
		    	return true;
		    }
		}
	}

	return false;
}


void DynamicObject::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}