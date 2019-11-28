#include "Object.h"
using namespace std;

Object::Object( Type t):type(t)
{ 
    dead=false;
    BOUNCER_SIZE=32;
    BOUNCER_SIZEX=32;
    if(t==OBSTACLE)
    { 
		BOUNCER_SIZEX=128; 
		image=al_load_bitmap("./resources/obstacle.png");
    }
}
Object::~Object()
{
    al_destroy_bitmap(image); 
}

Type Object::getType(){return type;}
void Object::setType(Type t){type=t;}

void Object::setBouncer_x(float x){bouncer_x=x;}
void Object::setBouncer_y(float y){bouncer_y=y;}

float Object::getBouncer_x(){return bouncer_x;}
float Object::getBouncer_y(){return bouncer_y;}

void Object::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}



