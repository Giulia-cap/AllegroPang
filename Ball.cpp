#include "Ball.h"
#include<iostream>
#include <random>
#include <cstdlib>
#include <time.h>
using namespace std;

Ball::Ball(int l,Type t,int s,float initialPosX, float initialPosY, float dx,float dy ):DynamicObject(l,t)
{
	BOUNCER_SIZE=s;
   
   bouncer_dx=dx;
   bouncer_dy=dy;
	bouncer_x = initialPosX / 2.0 - BOUNCER_SIZE / 2.0;
	bouncer_y = initialPosY / 2.0 - BOUNCER_SIZE / 2.0;
   cout<<"CREATA PALLA IN POSIZIONE : "<<bouncer_x<<" "<<bouncer_y<<endl;
	image= al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   al_set_target_bitmap(image);               /*  --------------------------> questo posso metterlo direttamente 
                                                         su object così non devo farlo nel main (vedi funzione init)*/
   al_clear_to_color(al_map_rgb(255, 0, 255)); /*idem*/
}

Ball::~Ball()
{ 
}

void Ball::move(int SCREEN_W,int SCREEN_H)
{
	 if(bouncer_x < 0 || bouncer_x > SCREEN_W - BOUNCER_SIZE) {  //invertire la direzione. Inseriamo la logica nell'evento timer, in modo che la bitmap che rimbalza 
            bouncer_dx = -bouncer_dx;                                //si sposti alla stessa velocità su qualsiasi computer.
         }

         if(bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE) {
            bouncer_dy = -bouncer_dy;
         }

         bouncer_x += bouncer_dx;
         bouncer_y += bouncer_dy;   
         if(bouncer_dy!=24)
         if(bouncer_dy>14.0) bouncer_dy-=0.3; // se aumenti il 24 aumenta anche la grandezza del salto
         else
         bouncer_dy+=0.3;
         
         //cout<<"X: "<<bouncer_dx<<" Y:"<<bouncer_dy<<endl;
}
void Ball::tick(){}
void Ball::render()
{   
	al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}   
void Ball::loadImage(){}
void Ball::die(){}