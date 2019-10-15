#include "DynamicObject.h"
using namespace std;

DynamicObject::DynamicObject(int l,Type t):Object(l,t){
	ttl=1000;
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