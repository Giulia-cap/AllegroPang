#include "Bullet.h"

 #include <iostream>
 using namespace std;

Bullet::Bullet(int l,Type t,float posx ,float posy):DynamicObject(l,t)
{
	BOUNCER_SIZE=10;
	image= al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	al_set_target_bitmap(image);               /*  --------------------------> questo posso metterlo direttamente 
																			su object così non devo farlo nel main (vedi funzione init)*/
    al_clear_to_color(al_map_rgb(255, 0, 255));
	bouncer_x=posx+4;
	bouncer_y=posy-50;
}
Bullet::~Bullet()
{
}

void Bullet::move(int SCREEN_W,int SCREEN_H)
{
	bouncer_y -= 3.0;
}
void Bullet::tick(){}
void Bullet::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}
void Bullet::loadImage(){}
void Bullet::die(){
}
