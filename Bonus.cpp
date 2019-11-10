#include "Bonus.h"

Bonus::Bonus(int l, Type t, int bt,int posX, int posY):DynamicObject(l,t)
{
	bonusType=(BonusType)bt;
	bouncer_x=posX;
	bouncer_y=posY;

	if(bonusType==OROLOGIO)
		image=al_load_bitmap("./resources/orologio.png");
	else if(bonusType==ARPIONE)
		image=al_load_bitmap("./resources/arpione.png");

	if(!image)
		cout<<"ERROR TO LOAD IMMAGE";
}


Bonus::~Bonus(){}

void Bonus::move(int a)
{
	if(bouncer_y<=(gameAreaH-32)) ///mettere variabile
		bouncer_y += 4.0;
}

void Bonus::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
	
}
void Bonus::die()
{
	 //if()
	
}