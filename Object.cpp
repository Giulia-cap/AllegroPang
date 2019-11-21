#include "Object.h"
using namespace std;

Object::Object( Type t):type(t){ dead=false;}
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


bool Object::collision(float xp, float yp, int sizep) //posizione e dimensione dell'oggetto con cui dobbiamo verificare se c'è stata la collisione
{
   if ((bouncer_x > xp + sizep ) || // is b1 on the right side of b2?
        (bouncer_y > yp + sizep ) || // is b1 under b2?
        (xp > bouncer_x + BOUNCER_SIZE ) || // is b2 on the right side of b1?
        (yp > bouncer_y + BOUNCER_SIZE ))   // is b2 under b1?
    {
        // no collision
        return false;
    }

    // collision
    return true;
}
