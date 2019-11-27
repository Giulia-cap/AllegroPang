#include "Ball.h"
#include<iostream>
#include <random>
#include <cstdlib>
#include <time.h>
using namespace std;

Ball::Ball(Type t,int s,float initialPosX, float initialPosY, float dx,float dy ):DynamicObject(t)
{
	BOUNCER_SIZE=s;
   BOUNCER_SIZEX=s;
   
   bouncer_dx=dx;
   bouncer_dy=dy;
	bouncer_x=initialPosX;
   bouncer_y=initialPosY;

   if(BOUNCER_SIZE>=48)multiplier=2.0;
   else if(BOUNCER_SIZE<=32 && BOUNCER_SIZE>16) multiplier =1.5;
   else multiplier =1;

   switch(s)
   {
      case 48:
      image=al_load_bitmap("./resources/ballGrande.png"); 
      break;
      case 32:
      image=al_load_bitmap("./resources/ballMedia.png"); 
      break;
      case 16:
      image=al_load_bitmap("./resources/ballPiccola.png"); 
   }
   if(!image)
      cout<<"ERROR TO LOAD IMMAGE";
}

Ball::~Ball()
{ 
}

void Ball::move()  
{
   if(bouncer_x <= 30 || bouncer_x +BOUNCER_SIZEX > (gameAreaW-40) ) 
      bouncer_dx = -bouncer_dx;    

   else if(bouncer_y > (gameAreaH) - BOUNCER_SIZE) 
   {
      bouncer_dy = -bouncer_dy; 
      collisionY=false; 
   }

   bouncer_x += bouncer_dx;
   bouncer_y += bouncer_dy;   
   if(bouncer_dy!=24)
   if(bouncer_dy>6.0*multiplier) bouncer_dy-=0.3; // se aumenti il 24 aumenta anche la grandezza del salto
   else bouncer_dy+=0.3;
}

