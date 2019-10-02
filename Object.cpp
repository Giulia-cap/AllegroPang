#include "Object.h"
using namespace std;

Object::Object( int l, Type t):life(l),type(t){}
Object::~Object(){al_destroy_bitmap(image);}
int Object::getLife(){return life;}
void Object::setLife(int l){life=l;}
Type Object::getType(){return type;}
void Object::setType(Type t){type=t;}
//ALLEGRO_BITMAP Object::getImage(){return image;}