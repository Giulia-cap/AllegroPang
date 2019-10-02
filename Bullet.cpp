#include "Bullet.h"

Bullet::Bullet(int l,Type t):DynamicObject(l,t)
{
	BOUNCER_SIZE=10;
	image= al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
}
Bullet::~Bullet()
{
	al_destroy_bitmap(image);
}

void Bullet::move(int bouncer_x, int bouncer_y)
{
   al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}
void Bullet::tick(){}
void Bullet::render(){}
void Bullet::loadImage(){}
void Bullet::die(){}