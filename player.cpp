
#include "Player.h"

Player::Player(int l,Type t):DynamicObject(l,t)
{
	BOUNCER_SIZE=32;

	image=al_load_bitmap("./resources/player/rightA.png");
	imagedx.push_back(image);
	image=al_load_bitmap("./resources/player/rightB.png");
	imagedx.push_back(image); 
	image=al_load_bitmap("./resources/player/leftA.png");
	imagesx.push_back(image);
	image=al_load_bitmap("./resources/player/leftB.png");
	imagesx.push_back(image); 
	image=al_load_bitmap("./resources/player/player.png");

  bouncer_x=(gameAreaW / 2.0) - (BOUNCER_SIZE / 2.0);
  bouncer_y=(gameAreaH - BOUNCER_SIZE );

	if(!image)
		cout<<"ERROR TO LOAD IMMAGE";
}

Player::~Player()
{
}

void Player::move(int k)
{
   if(k==0 && bouncer_x >= 4.0) //MOVIMENTO A SINISTRA
   {
   	  if(movSx<imagesx.size()-1) 
   	  	movSx++;
   	  else movSx=0;

   	  dx=false;
   	  sx=true;
   	  movDx=0;

      bouncer_x -= 4.0;
   }
   
   if(k==1 && bouncer_x <= gameAreaW - BOUNCER_SIZE - 4.0) //MOVIMENTO A DESTRA
   {
   	  if(movDx<imagedx.size()-1)
   	  	movDx++;
   	  else movDx=0;

   	  dx=true;
   	  sx=false;
   	  movSx=0;
   	  
      bouncer_x += 4.0;
   }
}

void Player::render()
{
	if(sx)
  		al_draw_bitmap(imagesx[movSx], bouncer_x, bouncer_y, 0);
  	else if(dx)
  		al_draw_bitmap(imagedx[movDx],bouncer_x, bouncer_y, 0);
}

void Player::die(){}

void Player::RemoveOneLife()
{
  if(life>0)
    life--;
}

void Player::reset()
{ 
  life=3;
  bouncer_x=(gameAreaW / 2.0) - (BOUNCER_SIZE / 2.0);
  bouncer_y=(gameAreaH - BOUNCER_SIZE );
}