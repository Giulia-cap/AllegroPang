#include "DynamicObject.h"
using namespace std;
int collDelay=0;
int collRate=10;
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
	
if(collDelay>=collDelay){
	if (bouncer_x+BOUNCER_SIZE<=x && bouncer_y <= y+sizey){ collisionX=true; collisionY=true;cout<<"angolo 1"<<endl;}
	else if (bouncer_x>=x+sizex && bouncer_y<=y+sizey) { collisionX=true; collisionY=true;cout<<"angolo 2"<<endl; }
	else
	{
	    if(bouncer_y <= y){collisionY=true; cout<<"COllisione sopra"<<endl;}
	    else if(bouncer_y >= y){collisionY=true; cout<<"Collisione forse sotto"<<endl;}
	}
	    
 
	collDelay=0;
   	changeMovement();
	return true;
}
collDelay++;
return false;
}

void DynamicObject::changeMovement()
{  
	if(collisionX){ //cout<<"vero"<<endl;
        bouncer_dx=-(bouncer_dx);
	}
    else if(collisionY){ //cout<<"vero"<<endl;
       bouncer_dy=-(bouncer_dy);
    }
    collisionX=false;
    collisionY=false;
}