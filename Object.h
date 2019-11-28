#include "includes.h"

#ifndef Object_H
#define Object_H

enum Type { PLAYER = 0, BALL, OBSTACLE, BONUS, WEAPONS, ANIMAL };

class Object
{
	protected:
		Type type;
		float bouncer_x;   //posizione oggetto
		float bouncer_y; 

	public:
		int BOUNCER_SIZE; //altezza
		int BOUNCER_SIZEX;//larghezza
		ALLEGRO_BITMAP *image=NULL;
		bool dead;

		Object(Type);
		virtual ~Object();

		Type getType();
		void setType(Type);

		void setBouncer_x(float);
		float getBouncer_x();

		void setBouncer_y(float);
		float getBouncer_y();
		
		virtual void render(); 
};

#endif

