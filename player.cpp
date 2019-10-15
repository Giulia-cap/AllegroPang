
#include "Player.h"
#include <iostream>
#include "allegro5/allegro_image.h"
//#include "allegro5/allegro_path.h"
using namespace std;

Player::Player(int l,Type t):DynamicObject(l,t)
{
	BOUNCER_SIZE=32;

	/*ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH); //--> funziona anche così
 	al_set_path_filename(path,"./resources/player.bmp");
 	image = al_load_bitmap(al_path_cstr(path, '/'));*/
	image=al_load_bitmap("./resources/player/rightA.png");
	imagedx.push_back(image);
	image=al_load_bitmap("./resources/player/rightB.png");
	imagedx.push_back(image); 
	image=al_load_bitmap("./resources/player/leftA.png");
	imagesx.push_back(image);
	image=al_load_bitmap("./resources/player/leftB.png");
	imagesx.push_back(image); 
	image=al_load_bitmap("./resources/player/player.png");

	if(!image)
		cout<<"ERROR TO LOAD IMMAGE";
}

Player::~Player()
{
}

void Player::move(int SCREEN_W,int k)
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
   
   if(k==1 && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) //MOVIMENTO A DESTRA
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

void Player::tick(){}
void Player::render()
{
	if(sx)
  		al_draw_bitmap(imagesx[movSx], bouncer_x, bouncer_y, 0);
  	else if(dx)
  		al_draw_bitmap(imagedx[movDx],bouncer_x, bouncer_y, 0);
}
void Player::loadImage(){}
void Player::die(){}