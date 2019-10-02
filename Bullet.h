#include "DynamicObject.h"
#ifndef Bullet_H
#define Bullet_H
class Bullet:public DynamicObject
{
	Bullet(int,Type);
	~Bullet();
	void tick();
	void render();
	void die();
  void move(int,int); 
  void loadImage();
};
#endif