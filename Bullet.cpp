#include "Bullet.h"

 #include <iostream>
 using namespace std;
ALLEGRO_BITMAP *chain;
Bullet::Bullet(int l,Type t,float posx ,float posy):DynamicObject(l,t)
{
	BOUNCER_SIZE=10;
    image=al_load_bitmap("./resources/anchor.png");
    chain=al_load_bitmap("./resources/coda.png");  
	bouncer_x=posx+4;
	bouncer_y=posy-50;
}
Bullet::~Bullet()
{
}

void Bullet::move(int SCREEN_W)
{
	if(bouncer_y>=5)
	bouncer_y -= 5.0;
}

void Bullet::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
	for(int i=bouncer_y;i<500-32;i++)
		if(i%32==0)
			al_draw_bitmap(chain, bouncer_x+3,i+10, 0);
}

void Bullet::die(){
}
