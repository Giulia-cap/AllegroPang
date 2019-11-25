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
	
	if( (bouncer_x+BOUNCER_SIZE<=x && bouncer_y <= y+sizey)
		|| (bouncer_x>=x+sizex && bouncer_y<=y+sizey) 
		|| (bouncer_x+BOUNCER_SIZE<=x && bouncer_y+BOUNCER_SIZE<=y)
		|| (bouncer_x>=x+sizex && bouncer_y+BOUNCER_SIZE>=y))
	{
		cout<<"angolo"<<endl;
		collisionY=true;
		collisionX=true;
	}
	else
	{
	    if(bouncer_y <= y+sizey){collisionY=true; }
	    else if(bouncer_x <= x + sizex )collisionX=true;
	    else if(x <= bouncer_x + BOUNCER_SIZE)collisionX=true;
	   	else if(y > bouncer_y + BOUNCER_SIZE)collisionY=true;
   	}

   	changeMovement();
	return true;
}

void DynamicObject::changeMovement()
{  
	if(collisionX){ cout<<"vero"<<endl;
        bouncer_dx=-(bouncer_dx);
	}
    else if(collisionY){ cout<<"vero"<<endl;
       bouncer_dy=-(bouncer_dy);
    }
    collisionX=false;
    collisionY=false;
}