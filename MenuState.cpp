#include "MenuState.h"
#include <iostream>
#include <iostream>

//ALLEGRO_EVENT_QUEUE *event_queue = NULL;


MenuState::MenuState(ALLEGRO_DISPLAY * & d,ALLEGRO_EVENT_QUEUE * &e,int w,int h):State(d,e,w,h){}

MenuState::~MenuState()
{

}


void MenuState::init()
{
	if(!al_install_mouse()) {
      cout<<"failed to initialize the mouse!"<<endl;
      return;
   }

   al_register_event_source(event_queue, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));
 
   al_flip_display();
}
bool dexit=false;
void MenuState::tick()
{
    while(!dexit)
    {
      	ALLEGRO_EVENT ev;
      	al_wait_for_event(event_queue, &ev);

	    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
	    	dexit=true;
	         return;
	      }

	    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	    {
	    	press=true;
	    	dexit=true;
	    }
		render();
	}

}


void MenuState::render()
{
	return;
}