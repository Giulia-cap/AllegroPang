#include <stdio.h>
#include <allegro5/allegro.h>
#include<iostream>
using namespace std;
#ifndef Object_H
#define Object_H

enum Type { PLAYER = 0, BALL, OBSTACLE, BONUS,BULLET };

class Object
{
	protected:
		int life;
		Type type;
		float bouncer_x;   //posizione oggetto
		float bouncer_y; 
		float gameAreaW=1100;
		float gameAreaH=500;
	public:
		int BOUNCER_SIZE; //dimensione quadrato
		ALLEGRO_BITMAP *image=NULL;

		Object(int,Type);
		virtual ~Object();

	 	int getLife();
		void setLife(int);

		Type getType();
		void setType(Type);


		void setBouncer_x(float);
		float getBouncer_x();

		void setBouncer_y(float);
		float getBouncer_y();

		bool collision(float, float, int);

		virtual void tick()=0;
		virtual void render()=0;
		virtual void die()=0;
		virtual void loadImage()=0;
		float getGameAreaW();
		float getGameAreaH();
};

#endif

