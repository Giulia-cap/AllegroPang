#include "Weapons.h"

ALLEGRO_BITMAP *chain;
Weapons::Weapons(Type t,float posx ,float posy):DynamicObject(t)
{
	BOUNCER_SIZE=10;
    image=al_load_bitmap("./resources/anchor.png");
    chain=al_load_bitmap("./resources/coda.png");  
	bouncer_x=posx+4;
	bouncer_y=posy-50;
}
Weapons::~Weapons()
{
}

void Weapons::move(int SCREEN_W)
{
	if(bouncer_y>=5)
		bouncer_y -= 5.0;
	else
		dead=true;
}

void Weapons::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
	for(int i=bouncer_y;i<500-32;i++)
		if(i%32==0)
			al_draw_bitmap(chain, bouncer_x+5,i+10, 0);
	
}

