#include "DynamicObject.h"
#ifndef Balls_H
#define Balls_H

class Balls:public DynamicObject
{
private:
	float bouncer_x;
   float bouncer_y;
   float bouncer_dx, bouncer_dy;
   bool redraw;
 	ALLEGRO_EVENT_QUEUE *event_queue;
 	 ALLEGRO_TIMER *timer = NULL;
	public:
		Balls(int,Type,int);
		~Balls();
		void move(int,int);
		void loadImage();
		void tick();
		void render();
		void die();
};
#endif