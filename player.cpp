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
	al_destroy_bitmap(image);
}

void Player::move(int bouncer_x, int bouncer_y)
{
   al_draw_bitmap(image, bouncer_x, bouncer_y, 0);
}
void Player::tick(){}
void Player::render(){}
void Player::loadImage(){}
void Player::die(){}