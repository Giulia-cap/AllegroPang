
#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(int l,Type t):DynamicObject(l,t)
{
	BOUNCER_SIZE=32;
	image= al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
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