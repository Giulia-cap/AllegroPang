#include "Bullet.h"

 #include <iostream>
 using namespace std;
ALLEGRO_BITMAP *chain;
Bullet::Bullet(int l,Type t,float posx ,float posy):DynamicObject(l,t)
{
	BOUNCER_SIZE=10;
	/*image= al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	chain= al_create_bitmap(5, 5);
	al_set_target_bitmap(chain);              
    al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(image);               
																			
    al_clear_to_color(al_map_rgb(255, 0, 255));*/
    image=al_load_bitmap("./resources/anchor.png");
    chain=al_load_bitmap("./resources/coda.png");  
	bouncer_x=posx+4;
	bouncer_y=posy-50;
}
Bullet::~Bullet()
{
}

void Bullet::move(int SCREEN_W,int SCREEN_H)
{
	if(bouncer_y>=5)
	bouncer_y -= 5.0;
}
void Bullet::tick(){}
void Bullet::render()
{
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
	for(int i=bouncer_y;i<640;i++)
	al_draw_bitmap(chain, bouncer_x+3,i, 0);
}
void Bullet::loadImage(){}
void Bullet::die(){
}
