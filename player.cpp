#include "Player.h"
#include <iostream>
#include "allegro5/allegro_image.h"
//#include "allegro5/allegro_path.h"
using namespace std;

Player::Player(int l,Type t):DynamicObject(l,t)
{
	BOUNCER_SIZE=32;
	/*ALLEGRO_PATH *path=al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_set_path_filename(path,"./resources/prova.png" );*/
	//image=al_load_bitmap("prova.png"); //image=al_load_bitmap("resources/prova.png"); al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE); 
	//image=al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE); 

   /*if(!image) {
      cout<<"ERROR TO LOAD IMMAGE";
   }*/

	/*bouncer_y=BOUNCER_SIZE-(21*2)-15; 
	bouncer_x=BOUNCER_SIZE/2.0 - 15;
	cout<<bouncer_y<<" "<<bouncer_x<<endl;*/

	image=al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE); 
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