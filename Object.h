#include <stdio.h>
#include <allegro5/allegro.h>
using namespace std;
#ifndef Object_H
#define Object_H

enum Type { PLAYER = 0, BALL, OBSTACLE, BONUS,BULLET };
class Object
{
	private:
		int life;
		Type type;
	public:
		int BOUNCER_SIZE;
		ALLEGRO_BITMAP *image;
		Object(int,Type);
		virtual ~Object();
	 	int getLife();
		void setLife(int);
		Type getType();
		void setType(Type);
		virtual void tick()=0;
		virtual void render()=0;
		virtual void die()=0;
		virtual void loadImage()=0;
};
#endif
