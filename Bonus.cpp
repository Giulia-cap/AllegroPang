#include "Bonus.h"

Bonus::Bonus(Type t, int bt,int posX, int posY):DynamicObject(t)
{
	bonusType=(BonusType)bt;
	bouncer_x=posX;
	bouncer_y=posY;
	BOUNCER_SIZE=20;
	BOUNCER_SIZEX=30;

	if(bonusType==OROLOGIO)
		image=al_load_bitmap("./resources/bonus/orologio.png");
	else if(bonusType==ARPIONE)
		image=al_load_bitmap("./resources/bonus/arpione.png");
	else if(bonusType==MACHINEGUN)
		image=al_load_bitmap("./resources/bonus/machineGun.png");
	else if(bonusType==ARPIONEX2)
		image=al_load_bitmap("./resources/bonus/arpionex2.png");
	else if(bonusType==CLESSIDRA)
		image=al_load_bitmap("./resources/bonus/clessidra.png");
	else if(bonusType==GIRANDOLA)
		image=al_load_bitmap("./resources/bonus/girandola.png");
	else if(bonusType==PROTEZIONE)
		image=al_load_bitmap("./resources/bonus/protezione.png");

	if(!image)
		cout<<"ERROR TO LOAD IMMAGE";
}


Bonus::~Bonus(){}

void Bonus::move()
{
	if( (bouncer_y+(BOUNCER_SIZE-10))<=(gameAreaH-32)) 
		bouncer_y += 4.0;
}
