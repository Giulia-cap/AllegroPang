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
	if(!collision(x,y,sizex,sizey)) return false;

		if(bouncer_y+BOUNCER_SIZE >= y || bouncer_y <= y+sizey )collisionY=true;
	    if(bouncer_x +BOUNCER_SIZE>= x || bouncer_x <= x+sizex  )collisionX=true;

   	changeMovement();
	return true;
}

void DynamicObject::changeMovement()
{  
	if(collisionX){
        bouncer_dx=bouncer_dx*-1;
       if(bouncer_dx>0)bouncer_x+=1;
       else bouncer_x-=1;
	}
    if(collisionY){
       bouncer_dy=bouncer_dy*-1;
       if(bouncer_dy>0)bouncer_y+=1;
       else bouncer_y-=1;
    }
    collisionX=false;
    collisionY=false;
}

void DynamicObject::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}