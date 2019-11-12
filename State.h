#ifndef State_H
#define State_H
#include <iostream>
#include <allegro5/allegro.h>

using namespace std;

class State
{
	protected:
		int SCREEN_W; 
		int SCREEN_H;
		ALLEGRO_DISPLAY *display;
		ALLEGRO_EVENT_QUEUE * event_queue;
		ALLEGRO_TIMER *timer = NULL;
		bool redraw=false;

	public:

		State(ALLEGRO_DISPLAY * & d, ALLEGRO_EVENT_QUEUE * & e,ALLEGRO_TIMER *t,int w,int h)
		{  SCREEN_W=w;
		   SCREEN_H=h;
		   display=d;
		   event_queue=e;
		   timer=t;
		}
		virtual ~State(){};
		virtual void init()=0;
		virtual void tick()=0;
		virtual void render()=0;

		/*State* getCurrentState(){return currentState;}
		void setCurrentState(State* s){currentState=s;}*/
};

#endif

