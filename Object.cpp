#include "Object.h"
using namespace std;

Object::Object( Type t):type(t)
{ 
    dead=false;
    BOUNCER_SIZE=32;
    BOUNCER_SIZEX=32;
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


bool Object::collision(float xp, float yp, int sizex, int sizey) //posizione e dimensione dell'oggetto con cui dobbiamo verificare se c'è stata la collisione
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


