
#include "includes.h"
#include "DynamicObject.h"

using namespace std;

#ifndef Parrot_H
#define Bunus_H

class Parrot:public DynamicObject
{
private:
	vector<ALLEGRO_BITMAP*> parrotAnimation;
	int anim=0;
	public:

		Parrot(Type,int);
		~Parrot();  
		void render();
		void move();
};
#endif
