#include "Bonus.h"

Bonus::Bonus(int l, Type t, BonusType bt,int posX, int posY):DynamicObject(l,t)
{
	bonusType=bt;
	bouncer_x=posX;
	bouncer_y=posY;
	image=al_load_bitmap("./resources/orologio.png");

	if(!image)
		cout<<"ERROR TO LOAD IMMAGE";
}


Bonus::~Bonus(){}

void Bonus::move(int a, int b)
{
	if(bouncer_y<=(gameAreaH-32)) ///mettere variabile
		bouncer_y += 4.0;
}

void Bonus::tick()
{
	 //if()
	
}

void Bonus::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
	
}
void Bonus::die()
{
	 //if()
	
}
void Bonus::loadImage()
{

}
