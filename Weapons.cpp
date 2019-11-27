#include "Weapons.h"

ALLEGRO_BITMAP *chain;
Weapons::Weapons(Type t,float posx ,float posy,string typeW):DynamicObject(t)
{
	typeWeapons=typeW;
	if(typeW=="machineGun")
	{
		ttl=100;
		BOUNCER_SIZE=32;
		BOUNCER_SIZEX=32;
	    image=al_load_bitmap("./resources/machineGun.png");
	}
	else
	{
		BOUNCER_SIZE=10;
		BOUNCER_SIZEX=12;
	    image=al_load_bitmap("./resources/anchor.png");
	    chain=al_load_bitmap("./resources/coda.png");  
	}
	bouncer_x=posx+4;
	bouncer_y=posy-50;
}
Weapons::~Weapons()
{
}

void Weapons::move()
{
	if(bouncer_y>=5 && !stop)
		bouncer_y -= 5.0;
	else
		dead=true;
}

void Weapons::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);

	if(typeWeapons=="hook")
	{
		for(int i=bouncer_y;i<500-32;i++)
			if(i%32==0)
				al_draw_bitmap(chain, bouncer_x+5,i+10, 0);	
	}
}

bool Weapons::collisionWithObstacle(float x, float y, int sizex, int sizey)
{
	if(!collision(x,y,sizex,sizey)) 
		return false;
	stop=true;
	return true;
}

