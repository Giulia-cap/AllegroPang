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

int collisionDelay=0;
int collisionRate=40;
bool DynamicObject::collisionWithObstacle(float x, float y, int sizex, int sizey)
{
		if(collisionDelay>collisionRate){

	if(!collision(x,y,sizex,sizey)) return false;

		if(bouncer_y+BOUNCER_SIZE >= y || bouncer_y <= y+sizey )collisionY=true;
	    if(bouncer_x +BOUNCER_SIZE>= x || bouncer_x <= x+sizex  )collisionX=true;
	    cout<<"bounc_x "<<bouncer_x<<" bouncer_y "<<bouncer_y<<endl;
	    cout<<"x matto "<<x<<" y matto "<<y<<endl;

   	changeMovement();
	return true;
		 collisionDelay=0;
}
collisionDelay++;
}

void DynamicObject::changeMovement()
{  
	if(collisionX){ cout<<"vero"<<endl;
        bouncer_dx=bouncer_dx*-1;
       if(bouncer_dx>0)bouncer_x+=1;
       else bouncer_x-=1;
	}
    if(collisionY){ cout<<"vero"<<endl;
       bouncer_dy=bouncer_dy*-1;
       if(bouncer_dy>0)bouncer_y+=1;
       else bouncer_y-=1;
    }
    collisionX=false;
    collisionY=false;
}
/*bool DynamicObject::collisionWithObstacle(float rect2x, float rect2y, int rect2width, int rect2height)
{
int rect1x=bouncer_x;
int rect1y=bouncer_y;
int rect1width=BOUNCER_SIZE;
int rect1height=BOUNCER_SIZE;
if(!collision(rect2x,rect2y,rect2width,rect2height)) return false;
		
   if(rect1x < rect2x + rect2width &&
   rect1x + rect1width > rect2x &&
   rect1y < rect2y + rect2height &&
   rect1y + rect1height > rect2y) 
	{ //il primo if serve a controllare se c'è una collisione
	if(rect1x < rect2x + rect2width || 
   rect1x + rect1width > rect2x) changeMovement(0,1);
  	else if( rect1y < rect2y + rect2height ||
   rect1y + rect1height > rect2y)changeMovement(1,0);

	}

return true;
}*/
void DynamicObject::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}