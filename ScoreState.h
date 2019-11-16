#include "State.h"
#include"Scoreboard.h"

#ifndef ScoreState_H
#define ScoreState_H

class ScoreState:public State
{
	private:
		ALLEGRO_FONT * pangFont;
		ALLEGRO_FONT *pangFontBig;
	public:
		ScoreState(ALLEGRO_DISPLAY * &, ALLEGRO_EVENT_QUEUE * &,ALLEGRO_TIMER * &, int,int);
		~ScoreState();
		void init();
		void tick();
		void render();
};
#endif