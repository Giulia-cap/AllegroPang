#include "Object.h"
using namespace std;

Object::Object( int l, Type t):life(l),type(t){}
Object::~Object(){al_destroy_bitmap(image);}

int Object::getLife(){return life;}
void Object::setLife(int l){life=l;}

Type Object::getType(){return type;}
void Object::setType(Type t){type=t;}

void Object::setBouncer_x(float x){bouncer_x=x;}
void Object::setBouncer_y(float y){bouncer_y=y;}

float Object::getBouncer_x(){return bouncer_x;}
float Object::getBouncer_y(){return bouncer_y;}


bool Object::collision(float xp, float yp, int sizep)
{
   if ((bouncer_x > xp + sizep - 1) || // is b1 on the right side of b2?
        (bouncer_y > yp + sizep - 1) || // is b1 under b2?
        (xp > bouncer_x + BOUNCER_SIZE - 1) || // is b2 on the right side of b1?
        (yp > bouncer_y + BOUNCER_SIZE - 1))   // is b2 under b1?
    {
        // no collision
        return false;
    }

    // collision
    return true;
}
//ALLEGRO_BITMAP Object::getImage(){return image;}