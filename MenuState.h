#include "State.h"
#ifndef MenuState_H
#define MenuState_H

class MenuState:public State
{
private:
		ALLEGRO_FONT * pangFont;
		ALLEGRO_FONT *pangFontBig;

		//IL CODICE SOPRA VA RIMOSSO E VA GENERALIZZATO NELL'INCLUDES.H
	public:
		MenuState(ALLEGRO_DISPLAY * &, ALLEGRO_EVENT_QUEUE * &,ALLEGRO_TIMER * &, int,int);
		~MenuState();
		void init();
		void tick();
		void render();


	bool press=false;
};
#endif