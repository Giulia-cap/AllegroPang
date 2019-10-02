#include "DynamicObject.h"
using namespace std;

DynamicObject::DynamicObject(int l,Type t):Object(l,t){}
DynamicObject::~DynamicObject(){}

void DynamicObject::setBouncer_x(float x){bouncer_x=x;}
void DynamicObject::setBouncer_y(float y){bouncer_y=y;}

float DynamicObject::getBouncer_x(){return bouncer_x;}
float DynamicObject::getBouncer_y(){return bouncer_y;}