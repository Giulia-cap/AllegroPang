#include "Weapons.h"

ALLEGRO_BITMAP *chain;
Weapons::Weapons(Type t,float posx ,float posy):DynamicObject(t)
{
	BOUNCER_SIZE=10;
	BOUNCER_SIZEX=12;
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
	if(bouncer_y>=5 && !stop)
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
	al_draw_rectangle( bouncer_x,  bouncer_y, bouncer_x+BOUNCER_SIZE, bouncer_y+BOUNCER_SIZE,
   al_map_rgb(255, 0, 0), 1);
}

void Weapons::changeMovement()
{
	stop=true;
}

