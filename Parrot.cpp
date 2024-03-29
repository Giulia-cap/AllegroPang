#include "Parrot.h"

Parrot::Parrot(Type t,int posX):DynamicObject(t)
{
	bouncer_x=posX;
	bouncer_y=100;
	BOUNCER_SIZE=32;

   image=al_load_bitmap("./resources/pappagallo1.png");
   parrotAnimation.push_back(image);
   image=al_load_bitmap("./resources/pappagallo2.png");
   parrotAnimation.push_back(image);
   image=al_load_bitmap("./resources/pappagallo3.png");
   parrotAnimation.push_back(image);
}


Parrot::~Parrot(){}

void Parrot::move()
{
	if( (bouncer_x+(BOUNCER_SIZE-10))<=(gameAreaW+64)) 
		bouncer_x += 4.0;
}
int animDelay=0;
int animRate=30;
void Parrot::render()
{
	al_draw_bitmap(parrotAnimation[anim], bouncer_x, bouncer_y, 0);
	if(animDelay>animRate){
	animDelay=0;
	anim++;
	}
	animDelay++;
	if(anim==3)anim=0;
}
	
	

