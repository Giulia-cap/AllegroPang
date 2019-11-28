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

bool DynamicObject::collision(float xp, float yp, int sizex, int sizey) //posizione e dimensione dell'oggetto con cui dobbiamo verificare se c'è stata la collisione
{
   if ((bouncer_x > xp + sizex ) || 
        (bouncer_y > yp + sizey ) || 
        (xp > bouncer_x + BOUNCER_SIZEX ) || 
        (yp > bouncer_y + BOUNCER_SIZE ))  
    {
        return false;
    }

    return true;
}


void DynamicObject::render()
{
	Object::render();
}