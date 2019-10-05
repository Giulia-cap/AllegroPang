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
	protected:
		float bouncer_x;   //posizione oggetto
		float bouncer_y; 
	public:
		int BOUNCER_SIZE; //dimensione quadrato
		ALLEGRO_BITMAP *image;

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
};
#endif

