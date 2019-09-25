#include "Balls.h"
#include<iostream>
using namespace std;

Balls::Balls(int l,Type t,int s):DynamicObject(l,t)
{
	BOUNCER_SIZE=s;
	event_queue = NULL;
	bouncer_x = 640 / 2.0 - BOUNCER_SIZE / 2.0;
    bouncer_y = 480 / 2.0 - BOUNCER_SIZE / 2.0;
    bouncer_dx = -4.0;
    bouncer_dy = 4.0;
    redraw = true;
	image= al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
}

Balls::~Balls()
{ 
   al_destroy_bitmap(image);
   al_destroy_event_queue(event_queue);
}

void Balls::move(int SCREEN_W,int SCREEN_H)
{
	/* ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {                           //logica del rimbalzo. Se il quadrato colpisce i bordi del display, 
         if(bouncer_x < 0 || bouncer_x > SCREEN_W - BOUNCER_SIZE) {  //invertire la direzione. Inseriamo la logica nell'evento timer, in modo che la bitmap che rimbalza 
            bouncer_dx = -bouncer_dx;                                //si sposti alla stessa velocità su qualsiasi computer.
         }

         if(bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE) {
            bouncer_dy = -bouncer_dy;
         }

         bouncer_x += bouncer_dx;
         bouncer_y += bouncer_dy;

         redraw = true;
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;

         al_clear_to_color(al_map_rgb(0,0,0));*/

         al_draw_bitmap(image, bouncer_x, bouncer_y, 0); //disegna la nostra bitmap sul display.
         // al_flip_display();
     // }
}
void Balls::tick(){}
void Balls::render(){}
void Balls::loadImage(){}
void Balls::die(){}