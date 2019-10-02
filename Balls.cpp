#include "Balls.h"
#include<iostream>
using namespace std;

Balls::Balls(int l,Type t,int s):DynamicObject(l,t)
{
	BOUNCER_SIZE=s;
	bouncer_x = 640 / 2.0 - BOUNCER_SIZE / 2.0;
	bouncer_y = 480 / 2.0 - BOUNCER_SIZE / 2.0;
	image= al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
}

Balls::~Balls()
{ 
   al_destroy_bitmap(image);
}

void Balls::move(int SCREEN_W,int SCREEN_H)
{
	 if(bouncer_x < 0 || bouncer_x > SCREEN_W - BOUNCER_SIZE) {  //invertire la direzione. Inseriamo la logica nell'evento timer, in modo che la bitmap che rimbalza 
            bouncer_dx = -bouncer_dx;                                //si sposti alla stessa velocità su qualsiasi computer.
         }

         if(bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE) {
            bouncer_dy = -bouncer_dy;
         }

         bouncer_x += bouncer_dx;
         bouncer_y += bouncer_dy;   
}
void Balls::tick(){}
void Balls::render()
{   
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}   
void Balls::loadImage(){}
void Balls::die(){}