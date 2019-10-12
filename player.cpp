
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

	image=al_load_bitmap("./resources/player.bmp"); 
	if(!image)
		cout<<"ERROR TO LOAD IMMAGE";
}

Player::~Player()
{
}

void Player::move(int SCREEN_W,int k)
{
   if(k==0 && bouncer_x >= 4.0) //MOVIMENTO A SINISTRA
      bouncer_x -= 4.0;
   
   if(k==1 && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) //MOVIMENTO A DESTRA
      bouncer_x += 4.0;
   
}

void Player::tick(){}
void Player::render()
{
  al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}
void Player::loadImage(){}
void Player::die(){}