#ifndef State_H
#define State_H
#include <iostream>
#include <allegro5/allegro.h>
using namespace std;

class State
{
	private:
		State *currentState;
	protected:
		int SCREEN_W; 
		int SCREEN_H;
		ALLEGRO_DISPLAY *display;
	public:

		State(ALLEGRO_DISPLAY * & d,int w,int h)
		{  SCREEN_W=w;
		   SCREEN_H=h;
		   display=d;
		}
		virtual ~State(){};
		virtual void init()=0;
		virtual void tick()=0;
		virtual void render()=0;

		State* getCurrentState(){return currentState;}
		void setCurrentState(State* s){currentState=s;}
};

#endif

